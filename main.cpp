#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
    const int argNumber = 5;
    if(argc != argNumber)
    {
        printf("Error: argc = %i, must be %i.\n", argc, argNumber);
        printf("numPointsW = atoi(argv[1]);\n");
        printf("numPointsH = atoi(argv[2]);\n");
        printf("radiusPoints = atoi(argv[3]);\n");
        printf("thiknessPoint = atoi(argv[4]);\n");
        return -1;
    }

    int numPointsW = atoi(argv[1]);
    int numPointsH = atoi(argv[2]);
    int radiusPoints = atoi(argv[3]);
    int thiknessPoint = atoi(argv[4]);

    const int mullFactor = 10;

    const int imageW = 1280*mullFactor;
    const int imageH = 960*mullFactor;

    const int imageFullW = 297*5*mullFactor;
    const int imageFullH = 210*5*mullFactor;

    Mat image = Mat::zeros(imageH, imageW, CV_8U);
    memset(image.ptr(0), 255, image.cols * image.rows);
    namedWindow("image", WINDOW_AUTOSIZE);

    Mat imageFull = Mat::zeros(imageFullH, imageFullW, CV_8U);
    memset(imageFull.ptr(0), 255, imageFull.cols * imageFull.rows);

    int rowStart = (imageFullH - imageH)/2;
    int colStart = (imageFullW - imageW)/2;

    int intervalW = imageW/(numPointsW+1);
    int intervalH = imageH/(numPointsH+1);

    if(imageW % (numPointsW+1) != 0)
        printf("Warning! intervalW is not integer, = %lf!\n",
               (double)imageW/((double)numPointsW+1.0));

    if(imageH % (numPointsH+1) != 0)
        printf("Warning! intervalH is not integer, = %lf!\n",
               (double)imageH/((double)numPointsH+1.0));

    int col = 0;
    int row = 0;

    radiusPoints = numPointsW >= numPointsH ? intervalW/12 : numPointsH/12;

    for(int r = 1; r < (numPointsH+1); r++)
    {
        row = r * intervalH;
        for(int c = 1; c < (numPointsW+1); c++)
        {
            col = c * intervalW;
            printf("(%i,%i)\n", row, col);
            circle(image, Point(col, row), radiusPoints, Scalar(0x00,0x00,0x00), thiknessPoint, 8 ,0);
        }
    }
    line(image, Point(0, 0), Point(imageW-1, 0), Scalar(0x00,0x00,0x00), 1, 8, 0);
    line(image, Point(imageW-1, 0), Point(imageW-1, imageH-1), Scalar(0x00,0x00,0x00), 1, 8, 0);
    line(image, Point(imageW-1, imageH-1), Point(0, imageH-1), Scalar(0x00,0x00,0x00), 1, 8, 0);
    line(image, Point(0, imageH-1), Point(0, 0), Scalar(0x00,0x00,0x00), 1, 8, 0);

    for(int i = 0; i < imageH; i++)
    {
        memcpy(imageFull.ptr(rowStart + i, colStart), image.ptr(i,0), image.cols);
    }


    for(;;)
    {
        char key = waitKey(1);
        if(key == 10)
        {
            char nameFile[64];
            sprintf(nameFile,"imageGrid%ix%ithick%i.png", numPointsW, numPointsH,thiknessPoint);
            imwrite(nameFile, image);
            imwrite("imageGrid.png", imageFull);
            break;
        }

        if(!image.empty())
            imshow("image", image);
    }

    cout << "Hello World!" << endl;
    return 0;
}
