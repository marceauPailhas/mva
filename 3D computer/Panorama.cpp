// Imagine++ project
// Project:  Panorama
// Author:   Pascal Monasse
// Date:     2013/10/08

#include <Imagine/Graphics.h>
#include <Imagine/Images.h>
#include <Imagine/LinAlg.h>
#include <vector>
#include <sstream>
using namespace Imagine;
using namespace std;

// Record clicks in two images, until right button click
void getClicks(Window w1, Window w2,
               vector<IntPoint2>& pts1, vector<IntPoint2>& pts2) {
IntPoint2 p1;
IntPoint2 p2;
Window w;
int sw;
//We don't know which window will be window 1 and window 2, so we record clicks and which window the click has been made on. We just have to pay attention to change window at each click. To have 4 points for (x,y) for the two images, we need to make 8 clicks.
for(size_t i=0; i<8; i++) {
  anyGetMouse(p1,w,sw);
  if (w==w1) {pts1.push_back(p1) ;}


  if (w==w2){pts2.push_back(p1) ;}
  }

}



// Return homography compatible with point matches
Matrix<float> getHomography(const vector<IntPoint2>& pts1,
                            const vector<IntPoint2>& pts2) {
    size_t n = min(pts1.size(), pts2.size());
    if(n<4) {
        cout << "Not enough correspondences: " << n << endl;
        return Matrix<float>::Identity(3);
    }
    Matrix<double> A(2*n,8);
    Vector<double> B(2*n);
    // We put the matrix defined at slide 21 of the first course
    for(size_t i=0; i<n; i++) {
    A(2*i,0)=pts1[i].x();A(2*i,1)=pts1[i].y();A(2*i,2)=1;A(2*i,3)=0;A(2*i,4)=0;A(2*i,5)=0;A(2*i,6)=-pts2[i].x() *pts1[i].x();A(2*i,7)=-pts2[i].x() *pts1[i].y();
    A(2*i+1,0)=0;A(2*i+1,1)=0;A(2*i+1,2)=0;A(2*i+1,3)=pts1[i].x();A(2*i+1,4)=pts1[i].y();A(2*i+1,5)=1;A(2*i+1,6)=-pts2[i].y() *pts1[i].x();A(2*i+1,7)=-pts2[i].y() *pts1[i].y();
    B[2*i]=pts2[i].x(); B[2*i+1]=pts2[i].y();}// ------------- TODO/A completer ----------

    B = linSolve(A, B);
    Matrix<float> H(3, 3);
    H(0,0)=B[0]; H(0,1)=B[1]; H(0,2)=B[2];
    H(1,0)=B[3]; H(1,1)=B[4]; H(1,2)=B[5];
    H(2,0)=B[6]; H(2,1)=B[7]; H(2,2)=1;

    // Sanity check
    for(size_t i=0; i<n; i++) {
        float v1[]={(float)pts1[i].x(), (float)pts1[i].y(), 1.0f};
        float v2[]={(float)pts2[i].x(), (float)pts2[i].y(), 1.0f};
        Vector<float> x1(v1,3);
        Vector<float> x2(v2,3);
        x1 = H*x1;
        cout << x1[1]*x2[2]-x1[2]*x2[1] << ' '
             << x1[2]*x2[0]-x1[0]*x2[2] << ' '
             << x1[0]*x2[1]-x1[1]*x2[0] << endl;
    }
    return H;
}

// Grow rectangle of corners (x0,y0) and (x1,y1) to include (x,y)
void growTo(float& x0, float& y0, float& x1, float& y1, float x, float y) {
    if(x<x0) x0=x;
    if(x>x1) x1=x;
    if(y<y0) y0=y;
    if(y>y1) y1=y;    
}

// Panorama construction
void panorama(const Image<Color,2>& I1, const Image<Color,2>& I2,
              Matrix<float> H) {
    Vector<float> v(3);
    float x0=0, y0=0, x1=I2.width(), y1=I2.height();

    v[0]=0; v[1]=0; v[2]=1;
    v=H*v; v/=v[2];
    growTo(x0, y0, x1, y1, v[0], v[1]);

    v[0]=I1.width(); v[1]=0; v[2]=1;
    v=H*v; v/=v[2];
    growTo(x0, y0, x1, y1, v[0], v[1]);

    v[0]=I1.width(); v[1]=I1.height(); v[2]=1;
    v=H*v; v/=v[2];
    growTo(x0, y0, x1, y1, v[0], v[1]);

    v[0]=0; v[1]=I1.height(); v[2]=1;
    v=H*v; v/=v[2];
    growTo(x0, y0, x1, y1, v[0], v[1]);

    cout << "x0 x1 y0 y1=" << x0 << ' ' << x1 << ' ' << y0 << ' ' << y1<<endl;

    Image<Color> I(int(x1-x0), int(y1-y0));
    setActiveWindow( openWindow(I.width(), I.height()) );
    I.fill(WHITE);

    Matrix<float> S; S = inverse(H); //needed to pull back the pixel in the image I1

        Vector<float> s(3);
           for (int i=0; i<I.width(); i++) {
               for (int j=0;j<I.height(); j++) {
                  v[0] = x0+i; v[1] = y0+j; v[2] = 1;
                  s = S*v; s/=s[2];

                  bool test1 = (s[0]>=0 && s[0]<I1.width() && s[1]>=0 && s[1]<I1.height()); // test if the pixel (pulled back) belongs to I1
                  bool test2 = (v[0]>=0 && v[0]<I2.width() && v[1]>=0 && v[1]<I2.height()); // test if the pixel belongs to I2

                  if (test1) I(i,j) = I1(int(s[0]), int(s[1]));
                  if (test2) I(i,j) = I2(int(v[0]), int(v[1]));

                  if (test1 && test2) { // we do the mean of the color if it belongs to both images.

                      int r1 =  I1(int(s[0]),int(s[1])).r();
                      int g1 =  I1(int(s[0]),int(s[1])).g();
                      int b1 =  I1(int(s[0]),int(s[1])).b();
                      int r2 =  I2(int(v[0]),int(v[1])).r();
                      int g2 =  I2(int(v[0]),int(v[1])).g();
                      int b2 =  I2(int(v[0]),int(v[1])).b();

                        // geometric mean because it seems to give better results
                        // possible explanation : our eye is sensible to the log of the intensity so a geometric mean might be more convenient
                      I(i,j).r() = int(sqrt(r1*r2));
                      I(i,j).g() = int(sqrt(g1*g2));
                      I(i,j).b() = int(sqrt(b1*b2));
                  }


               }
           } // ------------- TODO/A completer ----------
    display(I,0,0);
}

// Main function
int main(int argc, char* argv[]) {
    const char* s1 = argc>1? argv[1]: srcPath("image0006.jpg");
    const char* s2 = argc>2? argv[2]: srcPath("image0007.jpg");

    // Load and display images
    Image<Color> I1, I2;
    if( ! load(I1, s1) ||
        ! load(I2, s2) ) {
        cerr<< "Unable to load the images" << endl;
        return 1;
    }
    Window w1 = openWindow(I1.width(), I1.height(), s1);
    display(I1,0,0);
    Window w2 = openWindow(I2.width(), I2.height(), s2);
    setActiveWindow(w2);
    display(I2,0,0);

    // Get user's clicks in images
    vector<IntPoint2> pts1, pts2;
    getClicks(w1, w2, pts1, pts2);

    vector<IntPoint2>::const_iterator it;
    cout << "pts1="<<endl;
    for(it=pts1.begin(); it != pts1.end(); it++)
        cout << *it << endl;
    cout << "pts2="<<endl;
    for(it=pts2.begin(); it != pts2.end(); it++)
        cout << *it << endl;

    // Compute homography
    Matrix<float> H = getHomography(pts1, pts2);
    cout << "H=" << H/H(2,2);

    // Apply homography
    panorama(I1, I2, H);

    endGraphics();
    return 0;
}
