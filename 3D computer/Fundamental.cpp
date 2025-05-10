// Imagine++ project
// Project:  Fundamental
// Author:   Pascal Monasse

#include "./Imagine/Features.h"
#include <Imagine/Graphics.h>
#include <Imagine/LinAlg.h>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace Imagine;
using namespace std;

static const float BETA = 0.01f; // Probability of failure

struct Match {
    float x1, y1, x2, y2;
};

// Display SIFT points and fill vector of point correspondences
void algoSIFT(Image<Color,2> I1, Image<Color,2> I2,
              vector<Match>& matches) {
    // Find interest points
    SIFTDetector D;
    D.setFirstOctave(-1);
    Array<SIFTDetector::Feature> feats1 = D.run(I1);
    drawFeatures(feats1, Coords<2>(0,0));
    cout << "Im1: " << feats1.size() << flush;
    Array<SIFTDetector::Feature> feats2 = D.run(I2);
    drawFeatures(feats2, Coords<2>(I1.width(),0));
    cout << " Im2: " << feats2.size() << flush;

    const double MAX_DISTANCE = 100.0*100.0;
    for(size_t i=0; i < feats1.size(); i++) {
        SIFTDetector::Feature f1=feats1[i];
        for(size_t j=0; j < feats2.size(); j++) {
            double d = squaredDist(f1.desc, feats2[j].desc);
            if(d < MAX_DISTANCE) {
                Match m;
                m.x1 = f1.pos.x();
                m.y1 = f1.pos.y();
                m.x2 = feats2[j].pos.x();
                m.y2 = feats2[j].pos.y();
                matches.push_back(m);
            }
        }
    }
}

// RANSAC algorithm to compute F from point matches (8-point algorithm)
// Parameter matches is filtered to keep only inliers as output.

FMatrix<float,3,3> computeF(vector<Match>& matches) {

    const float distMax = 1.5f; // Pixel error for inlier/outlier discrimination
    int Niter=100000; // Adjusted dynamically
    FMatrix<float,3,3> bestF;
    vector<int> bestInliers;


    int n0=0; //the number of points x' which are as close as d from Hx for the best H so far
    int n; //the number of points x' which are as close as d from Hx for the best H at iteration n
    for(int iter=0; iter<Niter; iter++){
    Matrix<float> A(9,9);

    //We define each component of A
    for(int i=0; i<8; i++){
    int randIndex=rand()%matches.size();
    A(i,0)=matches[randIndex].x1*matches[randIndex].x2*0.000001f;A(i,1)=matches[randIndex].x1*matches[randIndex].y2*0.000001f;A(i,2)=matches[randIndex].x1*0.001f;
    A(i,3)=matches[randIndex].y1*matches[randIndex].x2*0.000001f;A(i,4)=matches[randIndex].y1*matches[randIndex].y2*0.000001f; A(i,5)=matches[randIndex].y1*0.001f;
    A(i,6)=matches[randIndex].x2*0.001f;A(i,7)=matches[randIndex].y2*0.001f;A(i,8)=1;

    };
    for(int j=0; j<9; j++){ A(8,j)=0;};



    //We do a SVD on A, f is the pseudo eigenvector with single value 0, and A is a function of the two points (x1,y1,1) and (x2,y2,1)

            Vector<float> S;
            Matrix<float> U,Vt,V;

            svd(A,U,S,Vt);
            V=transpose(Vt);
            Matrix<float> N(3,3);
            N(0,0)=0.001f;N(0,1)=0;N(0,2)=0;N(1,0)=0;N(1,1)=0.001f;N(1,2)=0;N(2,0)=0;N(2,1)=0; N(2,2)=1;
            Vector<float> FVector = V.getCol(2);
            Matrix<float> F(3,3);
            F(0,0)= FVector[0]; F(0,1)= FVector[1]; F(0,2)= FVector[2];
            F(1,0)= FVector[3]; F(1,1)= FVector[4]; F(1,2)= FVector[5];
            F(2,0)= FVector[6]; F(2,1)= FVector[7]; F(2,2)= FVector[8];

    F=N*F*N;
    n=0;

    Vector<float> D;
    Matrix<float> X,Yt,Y;
    svd(F,X,D,Yt);

    D[2] = 0;

    Matrix<float> Delta(3,3);
    Delta(0,0)=D[0],Delta(0,1)=0;Delta(0,2)=0;
    Delta(1,0)=0;Delta(1,1)=D[1],Delta(1,2)=0;
    Delta(2,0)=0;Delta(2,1)=0;Delta(2,2)=0;

    F=X*Delta*Yt;

    // We count how many inliers there are
    for (size_t MatchIndex=0; MatchIndex<matches.size(); MatchIndex++){
    float x;
    float y;
    float z;
    x = matches[MatchIndex].x1*F(0,0)+matches[MatchIndex].y1*F(1,0)+F(2,0);
    y = matches[MatchIndex].x1*F(0,1)+matches[MatchIndex].y1*F(1,1)+F(2,1);
    z = matches[MatchIndex].x1*F(0,2)+matches[MatchIndex].y1*F(1,2)+F(2,2);

    if(abs(x*matches[MatchIndex].x2+y*matches[MatchIndex].y2+z)/sqrt(pow(x,2)+pow(y,2)) < distMax ){ n = n+1;}
}

    // We store the best F we had so far
    if(n>n0){n0=n;
        bestF(0,0)=F(0,0);bestF(0,1)=F(0,1);bestF(0,2)=F(0,2);
        bestF(1,0)=F(1,0);bestF(1,1)=F(1,1);bestF(1,2)=F(1,2);
        bestF(2,0)=F(2,0);bestF(2,1)=F(2,1);bestF(2,2)=F(2,2);}
}
    // Setting the best in-liers

    for (size_t MatchIndex=0; MatchIndex< matches.size(); MatchIndex++){

    float x;
    float y;
    float z;
    x = matches[MatchIndex].x1*bestF(0,0)+matches[MatchIndex].y1*bestF(1,0)+bestF(2,0);
    y = matches[MatchIndex].x1*bestF(0,1)+matches[MatchIndex].y1*bestF(1,1)+bestF(2,1);
    z = matches[MatchIndex].x1*bestF(0,2)+matches[MatchIndex].y1*bestF(1,2)+bestF(2,2);

    if(abs(x*matches[MatchIndex].x2+y*matches[MatchIndex].y2+z)/sqrt(pow(x,2)+pow(y,2)) < distMax ){bestInliers.push_back(MatchIndex);};
}
  // now we re-evaluate the model over all the in-liers

    Matrix<float> A(bestInliers.size(),9);

    //We define each component of A
    for(size_t i=0; i<bestInliers.size(); i++){
    A(i,0)=matches[bestInliers[i]].x1*matches[bestInliers[i]].x2*0.000001f;A(i,1)=matches[bestInliers[i]].x1*matches[bestInliers[i]].y2*0.000001f;A(i,2)=matches[bestInliers[i]].x1*0.001f;
    A(i,3)=matches[bestInliers[i]].y1*matches[bestInliers[i]].x2*0.000001f;A(i,4)=matches[bestInliers[i]].y1*matches[bestInliers[i]].y2*0.000001f; A(i,5)=matches[bestInliers[i]].y1*0.001f;
    A(i,6)=matches[bestInliers[i]].x2*0.001f;A(i,7)=matches[bestInliers[i]].y2*0.001f;A(i,8)=1;
    };

    //We solve the linear system transpose(A)f=0 where f is the unknown, and A is a function of the two points

    //computes F
    Vector<float> S1;
    Matrix<float> U1,V1t,V1;
    cout << "we are going to compute F with minimal distance"<<endl;
    cout << "A="<< A << endl;
    svd(A,U1,S1,V1t);
    V1=transpose(V1t);
    Matrix<float> N(3,3);
    N(0,0)=0.001f;N(0,1)=0;N(0,2)=0;N(1,0)=0;N(1,1)=0.001f;N(1,2)=0;N(2,0)=0;N(2,1)=0; N(2,2)=1;
    Vector<float> FVector = V1.getCol(2);

    // We set the smaller single value of F to 0
    Matrix<float> F(3,3);
    F(0,0)= FVector[0]; F(0,1)= FVector[1]; F(0,2)= FVector[2];
    F(1,0)= FVector[3]; F(1,1)= FVector[4]; F(1,2)= FVector[5];
    F(2,0)= FVector[6]; F(2,1)= FVector[7]; F(2,2)= FVector[8];

    F=N*F*N;
    n=0;

    Vector<float> D1;
    Matrix<float> X1,Y1t,Y1;
    svd(F,X1,D1,Y1t);

    D1[2] = 0;

    Matrix<float> Delta1(3,3);
    Delta1(0,0)=D1[0],Delta1(0,1)=0;Delta1(0,2)=0;
    Delta1(1,0)=0;Delta1(1,1)=D1[1],Delta1(1,2)=0;
    Delta1(2,0)=0;Delta1(2,1)=0;Delta1(2,2)=0;

    F=X1*Delta1*Y1t; // we recomputed F and we set the smaller eigenvalue to 0

    //We update the bestF

    bestF(0,0)=F(0,0);bestF(0,1)=F(0,1);bestF(0,2)=F(0,2);
    bestF(1,0)=F(1,0);bestF(1,1)=F(1,1);bestF(1,2)=F(1,2);
    bestF(2,0)=F(2,0);bestF(2,1)=F(2,1);bestF(2,2)=F(2,2);

    // --------------- TODO ------------
    // DO NOT FORGET NORMALIZATION OF POINTS


    // Updating matches with inliers only
    vector<Match> all=matches;
    matches.clear();
    for(size_t i=0; i<bestInliers.size(); i++)
    {matches.push_back(all[bestInliers[i]]);}

    return bestF;
}

// Expects clicks in one image and show corresponding line in other image.
// Stop at right-click.
void displayEpipolar(Image<Color> I1, Image<Color> I2,
                     const FMatrix<float,3,3>& F) {

    while(true) {
        FVector<float,3> X1,X2;
        int w = I1.width();
        int h = I1.height();

        int x,y;
        if(getMouse(x,y) == 3)
            break;
        getMouse(x,y);
        cout<< "x="<<x<<", y="<< y<<endl;

        if (x<w) {X1[0]=x-w/2;X1[1]=y-h/2; X1[2]=1; // we don't forget to convert position of one point on the image into position on the camera screen
            X2 = transpose(F)*X1;
            float u = -(1/X2[1])*((-w/2)*X2[0]+1); // all lines cross the line of equation x=-w/2 and x=w/2, even if it is outside the photo
            float v = -(1/X2[1])*((+w/2)*X2[0]+1);
            drawLine(int(w+w/2),int((h/2)+u),int(w+w/2+w/2),int((h/2)+v),RED);}// we don't forget to convert back (x,y) of the camera into (x,y) of the photo


        if (x>w){X2[0]=x-3*w/2;X2[1]=y-h/2; X2[2]=1; //Same remarks as for above

            X1 = F*X2;
            float u =-(1/X1[1])*((-w/2)*X1[0]+1);
            float v = -(1/X1[1])*((+w/2)*X1[0]+1);
            drawLine(int(w/2 - w/2),int(h/2 +u),int(w/2 +w/2),int(h/2+v),RED);}

        // --------------- TODO ------------
    }
}

int main(int argc, char* argv[])
{
    srand((unsigned int)time(0));

    const char* s1 = argc>1? argv[1]: srcPath("im1.jpg");
    const char* s2 = argc>2? argv[2]: srcPath("im2.jpg");

    // Load and display images
    Image<Color,2> I1, I2;
    if( ! load(I1, s1) ||
        ! load(I2, s2) ) {
        cerr<< "Unable to load images" << endl;
        return 1;
    }
    int w = I1.width();
    openWindow(2*w, I1.height());
    display(I1,0,0);
    display(I2,w,0);

    vector<Match> matches;
    algoSIFT(I1, I2, matches);
    const int n = (int)matches.size();
    cout << " matches: " << n << endl;
    drawString(100,20,std::to_string(n)+ " matches",RED);
    click();
    
    FMatrix<float,3,3> F = computeF(matches);
    cout << "F="<< endl << F;

    // Redisplay with matches
    display(I1,0,0);
    display(I2,w,0);
    for(size_t i=0; i<matches.size(); i++) {
        Color c(rand()%256,rand()%256,rand()%256);
        fillCircle(matches[i].x1+0, matches[i].y1, 2, c);
        fillCircle(matches[i].x2+w, matches[i].y2, 2, c);        
    }
    drawString(100, 20, to_string(matches.size())+"/"+to_string(n)+" inliers", RED);
    click();

    // Redisplay without SIFT points
    display(I1,0,0);
    display(I2,w,0);
    displayEpipolar(I1, I2, F);

    endGraphics();
    return 0;
}
