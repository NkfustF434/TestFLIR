#include <opencv2\highgui\highgui.hpp>
#include <fstream>
#include <bitset>

void Quantization(cv::Mat clsInputImage, cv::Mat& clsOutputImage)
{
	std::fstream clsWrite14, clsWrite8;
	clsWrite14.open("D:\\14R.txt", std::ios::out);
	clsWrite8.open("D:\\8Q.txt", std::ios::out);
	int iMaxValue = 0;
	clsOutputImage = cv::Mat::zeros(clsInputImage.rows, clsInputImage.cols, CV_8UC1);
	if (!clsInputImage.empty()){
		for (size_t i = 0; i < clsInputImage.rows; i++)
		{
			for (size_t j = 0; j < clsInputImage.cols; j++)
			{
				if (clsInputImage.at<unsigned short>(i, j)>iMaxValue)
					iMaxValue = clsInputImage.at<unsigned short>(i, j);

			}
		}
		float fRatio = 255.0 / iMaxValue;
		for (size_t i = 0; i < clsInputImage.rows; i++)
		{
			for (size_t j = 0; j < clsInputImage.cols; j++)
			{
				int iValue = clsInputImage.at<unsigned short>(i, j)*fRatio;
				clsOutputImage.at<unsigned char>(i, j) = iValue;
				clsWrite14 << std::bitset<16>(clsInputImage.at<unsigned short>(i, j));
				clsWrite14 << ',';
				clsWrite8 << iValue;
				clsWrite8 << ',';
			}
			clsWrite14 << std::endl;
			clsWrite8 << std::endl;
		}

	}
	clsWrite8.close();
	clsWrite14.close();
}

void main()
{

	cv::Mat clsInputImage = cv::imread("D:\\t14.tiff", cv::IMREAD_ANYDEPTH);
	cv::Mat clsOutputImage = cv::Mat::zeros(clsInputImage.rows, clsInputImage.cols, CV_8UC1);
	Quantization(clsInputImage, clsOutputImage);
	cv::imshow("8Q", clsOutputImage);
	cvWaitKey();

}