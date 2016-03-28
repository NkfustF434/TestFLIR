#import "photonSDK.dll"
#include <sstream>
#include <opencv2\highgui\highgui.hpp>
#include "comp14.h"
#include <fstream>
#include <bitset>
#include <time.h>

Photon::IPhotonCamPtr m_pThermalCam;
Photon::ITauPtr m_pTau;
int iDatas[512][640];
unsigned short TempImg[512][640];

void Quantization(cv::Mat clsInputImage, cv::Mat& clsOutputImage)
{
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
			}
		}

	}
}

void Snap()
{
	Photon::Result result;
	short correctionMask = 0;
	short captureBuffer = 0x0800 | 0x0006;  // Snapshot and frame 6

	// Get the current correction mask
	result = m_pThermalCam->GetCorrectionMask(&correctionMask);
	// Capture video data and store in camera snapshot buffer
	result = m_pThermalCam->CaptureFrames(captureBuffer);
	// Set the correction mask to its original state
	result = m_pThermalCam->SetCorrectionMask(correctionMask);

}

void Retrieve8()
{

	Photon::Result result;
	short width = 160;
	short height = 128;
	unsigned long snapShotAddress = 0x00000000;
	short fpaType = 0;
	short blindRows = 0;
	long addrIncrement = 0;
	int bytes = 0;
	short line[160];
	result = m_pTau->GetFPAType(&fpaType);
	result = m_pTau->GetSnapshotAddress(0, &snapShotAddress);
	result = m_pThermalCam->GetFPAExtents(&width, &height, &blindRows);
	height = height - blindRows;
	unsigned char bLine[2048];
	unsigned char spBytes[640];

	//取得Raw Data-----------------------------------------//
	for (int row = 0; row < height; row++)
	{
		result = m_pTau->ReadRawSnapshotData(snapShotAddress, (short)width, (unsigned char**)&spBytes);
		snapShotAddress += width;
		for (int col = 0; col < width; col++)
		{
			TempImg[row][col] = spBytes[col];
		}
	}

	//放回影像-----------------------------------------//
	cv::Mat clsImg = cv::Mat::zeros(height, width, CV_8UC1);
	std::fstream clsWrite;
	clsWrite.open("D:\\8.txt", std::ios::out);
	for (size_t i = 0; i < height; i++)
	{
		for (size_t j = 0; j < width; j++)
		{
			clsImg.at<unsigned char>(height - i - 1, j) = TempImg[i][j];
			int iO = TempImg[i][j];
			clsWrite << iO;
			clsWrite << ',';
		}
		clsWrite << std::endl;
	}
	clsWrite.close();
	cv::imwrite("D:\\8.bmp", clsImg);
	cv::imshow("8-Bit", clsImg);
	cv::waitKey(0);
}

void Retrieve14()
{

	Photon::Result result;
	short width = 160;
	short height = 128;
	unsigned long snapShotAddress = 0x00000000;
	short fpaType = 0;
	short blindRows = 0;
	long addrIncrement = 0;
	int bytes = 0;
	short line[160];
	result = m_pTau->GetFPAType(&fpaType);
	result = m_pTau->GetSnapshotAddress(0, &snapShotAddress);
	result = m_pThermalCam->GetFPAExtents(&width, &height, &blindRows);
	height = height - blindRows;
	unsigned char spBytes[640];

	unsigned char TempLine[512 * 640];


	//取得Raw Data-----------------------------------------//
	for (int row = 0; row < height; row++)
	{
		for (size_t i = 0; i < 640; i++)
		{
			spBytes[i] = 0;
		}

		if (row == height)
			printf("");
		result = m_pTau->ReadRawSnapshotData(snapShotAddress, (short)width, (unsigned char**)&TempLine[row*width]);

		snapShotAddress += width;
	}

	//解壓縮14Bit-----------------------------------------//
	int buf_cnt = 0;
	int  row_cnt = 0;
	int col_cnt = 0;
	int iPixel = 0;
	int iTest = 0;
	while (buf_cnt < height*width)
	{
		iTest++;
		int iInput = TempLine[buf_cnt];
		if (iInput & 0x80)
		{
			iPixel = iPixel + (iInput & 0x7F) - 64;
		}
		else if (iInput & 0x40)
		{
			iPixel = iPixel + ((iInput >> 3) & 7) - 4;
			TempImg[row_cnt][col_cnt] = iPixel;

			col_cnt += 1;
			if (col_cnt >= 640)
			{
				col_cnt = 0;
				row_cnt += 1;
				if (buf_cnt % 2)// Check for unaligned end of video line
				{
					buf_cnt += 1;  // Discard one byte to realign.
				}

			}

			iPixel = iPixel + (TempLine[buf_cnt] & 7) - 4;// Set up second result.

		}
		else
		{
			iPixel = (iInput << 8) + TempLine[buf_cnt + 1];
			buf_cnt += 1;

		}

		TempImg[row_cnt][col_cnt] = iPixel;

		buf_cnt += 1;

		col_cnt += 1;

		if (col_cnt >= 640)
		{
			col_cnt = 0;

			row_cnt += 1;

			if (buf_cnt % 2) // Check for unaligned end of video line
				buf_cnt += 1; // Discard one byte to realign.

		}
	}



	//放回影像------------------------------------------------//
	cv::Mat clsImg = cv::Mat::zeros(height, width, CV_16UC1);
	clsImg = cv::Scalar::all(0x0000);

	std::fstream clsWrite;
	clsWrite.open("D:\\14.txt", std::ios::out);

	for (size_t i = 0; i < height; i++)
	{
		for (size_t j = 0; j < width; j++)
		{
			clsImg.at<unsigned short>(i, j) = TempImg[i][j];
			clsWrite << std::bitset<16>(TempImg[i][j]);
			clsWrite << ',';
		}
		clsWrite << std::endl;
	}
	clsWrite.close();
	cv::imwrite("D:\\14.tiff", clsImg);
	cv::imshow("14-Bit", clsImg);

	cv::Mat clsImage;
	Quantization(clsImg, clsImage);
	cv::imshow("8-Bit", clsImage);

}

void main()
{
	::CoInitialize(NULL);
	m_pTau.CreateInstance(__uuidof(Photon::Tau));

	//連線相機

	m_pThermalCam.CreateInstance(__uuidof(Photon::PhotonCam));
	if (m_pThermalCam == nullptr)
	{
		printf("CreateInstance error!\n");
	}

	Photon::Result result = m_pThermalCam->OpenComm("COM3");

	if (result < Photon::Result::CAM_OK)
	{
		printf("OpenComm error!\n");
	}


	//校正
	//m_pThermalCam->DoFFC();
	//Sleep(2000);

	//設定裝置ID
	int deviceId;
	result = m_pThermalCam->GetSDKDeviceId(&deviceId);
	result = m_pTau->SetSDKDeviceId(deviceId);


	//清除ROM裡面的影像
	//result = m_pTau->ClearSnapshots();
	//Sleep(2000);

	clock_t clkStart = clock();

	//拍照
	Snap();
	Sleep(2000);

	//成像(14bit/8bit)
	Retrieve14();

	//計算時間
	printf("Cost Time: %d", clock() - clkStart);

	cv::waitKey(0);

}
