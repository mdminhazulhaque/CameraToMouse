#include <opencv2/opencv.hpp>
#include <QApplication>
#include <QCursor>

using namespace cv;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    VideoCapture webcam;
    Mat imgSrc;
    Mat imgThrs;
    Moments m;

    QCursor cursor;
    char key;

    // Open webcam, make sure the device is installed correctly
    webcam.open(0);

    while(webcam.read(imgSrc))
    {
        // Flip the webcam capture
        flip(imgSrc, imgSrc, 1);
        imgThrs = Mat(imgSrc.rows, imgSrc.cols, imgSrc.type());
        // Convert the image from BGR to HLS
        cvtColor(imgSrc, imgSrc, CV_BGR2HLS);
        // Filter object color
        inRange(imgSrc, Scalar(50,50,20), Scalar(80,120,50), imgThrs);
        // Blur it to remove noise
        GaussianBlur(imgThrs, imgThrs, Size(), 5);
        // Thresh it to get contours
        threshold(imgThrs, imgThrs, 200, 255, CV_THRESH_BINARY);
        // Get moments
        m = moments(imgThrs, true);
        // And center
        cursor.setPos(m.m10/m.m00 * 2.13, m.m01/m.m00 * 1.6);
        // Resize frame, 50% smaller
        resize(imgSrc, imgSrc, Size(), 0.5, 0.5, INTER_NEAREST);
        // Show the webcam frame
        imshow("webcam", imgSrc);
        key = waitKey(10);

        // If key == Esc
        if(key==27)
            break;
    }

    webcam.release();
    return 0;
}
