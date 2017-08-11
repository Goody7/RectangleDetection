
// Task6Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Task6.h"
#include "Task6Dlg.h"
#include "afxdialogex.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTask6Dlg �Ի���




CTask6Dlg::CTask6Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTask6Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTask6Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTask6Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OP_BUTTON, &CTask6Dlg::OnBnClickedOpenButton)
	ON_BN_CLICKED(IDC_DET_BUTTON, &CTask6Dlg::OnBnClickedDetButton)
END_MESSAGE_MAP()


// CTask6Dlg ��Ϣ�������

BOOL CTask6Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CTask6Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTask6Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CTask6Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

CImage image,image1; //����ͼƬ�� 
void CTask6Dlg::OnBnClickedOpenButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ���ù�����   
    TCHAR szFilter[] = _T("Image files(*.png; *.jpg;*.bmp)|*.png;*.jpg;*.bmp|All files(*.*)|*.*||");   
    // ������ļ��Ի���   
    CFileDialog fileDlg(TRUE,NULL,NULL,OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST|OFN_READONLY, szFilter, NULL);   
    CString strFilePath; 

	GetDlgItem(IDC_SHOWOP)->Invalidate(true);//ˢ�¿ؼ�
	image.Destroy();

	//��ʾͼƬ
	if (IDOK == fileDlg.DoModal())   
    { 
       // ���������ļ��Ի����ϵġ��򿪡���ť����ѡ���ͼƬ��ʾ��ͼƬ�ؼ���   
       strFilePath = fileDlg.GetPathName(); 
       image.Load(strFilePath); //����ͼƬ·������ͼƬ  
       CRect rect;//��������� 
	   CRect rect1;
       int width = image.GetWidth();//��ȡͼƬ���  
       int height = image.GetHeight();//��ȡͼƬ�߶�  
  
       GetDlgItem(IDC_SHOWOP)->GetWindowRect(&rect);//�����ھ���ѡ�е�picture�ؼ���  
       ScreenToClient(&rect);//���ͻ���ѡ�е�Picture�ؼ���ʾ�ľ���������
  
       CWnd *pWnd=GetDlgItem(IDC_SHOWOP);//���pictrue�ؼ����ڵľ��  
       pWnd->GetClientRect(&rect);//���pictrue�ؼ����ڵľ�������  
       CDC *pDC=pWnd->GetDC();//���pictrue�ؼ���DC 
	   //SetStretchBltMode(pDC->m_hDC,STRETCH_HALFTONE); 
       //image.StretchBlt(pDC->m_hDC,rect,SRCCOPY); 

	   if(width<=rect.Width() && height<=rect.Width()) //���ͼƬ�ĳߴ�С��ͼƬ�ؼ��ߴ磬��������ʾ  
       {  
            rect1 = CRect(rect.TopLeft(), CSize(width,height));  
			SetStretchBltMode(pDC->m_hDC,STRETCH_HALFTONE); 
            image.StretchBlt(pDC->m_hDC,rect1,SRCCOPY); 
       }  
       else//���ͼƬ�ĳߴ����ͼƬ�ؼ��ĳߴ�  
       {  
            float xScale=(float)rect.Width()/(float)width;//��X�������������  
            float yScale=(float)rect.Height()/(float)height;//��Y�������������  
            float ScaleIndex=(xScale<=yScale?xScale:yScale);  
            rect1 = CRect(rect.TopLeft(), CSize((int)width*ScaleIndex,(int)height*ScaleIndex)); 
			SetStretchBltMode(pDC->m_hDC,STRETCH_HALFTONE); 
            image.StretchBlt(pDC->m_hDC,rect1,SRCCOPY); 
        }  
        ReleaseDC(pDC);//�ͷ�picture�ؼ���DC 
     } 


}

void MatToCImage(Mat& mat, CImage& cimage)  
{  
    if (0 == mat.total())  
    {  
        return;  
    }  
  
  
    int nChannels = mat.channels();  
    if ((1 != nChannels) && (3 != nChannels))  
    {  
        return;  
    }  
    int nWidth    = mat.cols;  
    int nHeight   = mat.rows;  
  
  
    //�ؽ�cimage  
    cimage.Destroy();  
    cimage.Create(nWidth, nHeight, 8 * nChannels);  
  
  
    //��������  
  
  
    uchar* pucRow;                                  //ָ������������ָ��  
    uchar* pucImage = (uchar*)cimage.GetBits();     //ָ����������ָ��  
    int nStep = cimage.GetPitch();                  //ÿ�е��ֽ���,ע���������ֵ�����и�  
  
  
    if (1 == nChannels)                             //���ڵ�ͨ����ͼ����Ҫ��ʼ����ɫ��  
    {  
        RGBQUAD* rgbquadColorTable;  
        int nMaxColors = 256;  
        rgbquadColorTable = new RGBQUAD[nMaxColors];  
        cimage.GetColorTable(0, nMaxColors, rgbquadColorTable);  
        for (int nColor = 0; nColor < nMaxColors; nColor++)  
        {  
            rgbquadColorTable[nColor].rgbBlue = (uchar)nColor;  
            rgbquadColorTable[nColor].rgbGreen = (uchar)nColor;  
            rgbquadColorTable[nColor].rgbRed = (uchar)nColor;  
        }  
        cimage.SetColorTable(0, nMaxColors, rgbquadColorTable);  
        delete []rgbquadColorTable;  
    }  
  
  
    for (int nRow = 0; nRow < nHeight; nRow++)  
    {  
        pucRow = (mat.ptr<uchar>(nRow));  
        for (int nCol = 0; nCol < nWidth; nCol++)  
        {  
            if (1 == nChannels)  
            {  
                *(pucImage + nRow * nStep + nCol) = pucRow[nCol];  
            }  
            else if (3 == nChannels)  
            {  
                for (int nCha = 0 ; nCha < 3; nCha++)  
                {  
                    *(pucImage + nRow * nStep + nCol * 3 + nCha) = pucRow[nCol * 3 + nCha];  
                }             
            }  
        }     
    }  
}  

void CImageToMat(CImage& cimage, Mat& mat)  
{  
    if (true == cimage.IsNull())  
    {  
        return;  
    }  
  
  
    int nChannels = cimage.GetBPP() / 8;  
    if ((1 != nChannels) && (3 != nChannels))  
    {  
        return;  
    }  
    int nWidth    = cimage.GetWidth();  
    int nHeight   = cimage.GetHeight();  
  
  
    //�ؽ�mat  
    if (1 == nChannels)  
    {  
        mat.create(nHeight, nWidth, CV_8UC1);  
    }  
    else if(3 == nChannels)  
    {  
        mat.create(nHeight, nWidth, CV_8UC3);  
    }  
  
  
    //��������  
  
  
    uchar* pucRow;                                  //ָ������������ָ��  
    uchar* pucImage = (uchar*)cimage.GetBits();     //ָ����������ָ��  
    int nStep = cimage.GetPitch();                  //ÿ�е��ֽ���,ע���������ֵ�����и�  
  
  
    for (int nRow = 0; nRow < nHeight; nRow++)  
    {  
        pucRow = (mat.ptr<uchar>(nRow));  
        for (int nCol = 0; nCol < nWidth; nCol++)  
        {  
            if (1 == nChannels)  
            {  
                pucRow[nCol] = *(pucImage + nRow * nStep + nCol);  
            }  
            else if (3 == nChannels)  
            {  
                for (int nCha = 0 ; nCha < 3; nCha++)  
                {  
                    pucRow[nCol * 3 + nCha] = *(pucImage + nRow * nStep + nCol * 3 + nCha);  
                }             
            }  
        }     
    }  
} 

static void getBinMask( const Mat& comMask, Mat& binMask )
{
    if( comMask.empty() || comMask.type()!=CV_8UC1 )
        CV_Error( CV_StsBadArg, "comMask is empty or has incorrect type (not CV_8UC1)" );
    if( binMask.empty() || binMask.rows!=comMask.rows || binMask.cols!=comMask.cols )
        binMask.create( comMask.size(), CV_8UC1 );
    binMask = comMask & 1;
}

void CTask6Dlg::OnBnClickedDetButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Mat srcImage,dstImage,grayImage,edgeImage,dilateImg;
	CImageToMat(image, srcImage);//CImageת��ΪMat
	//GetDlgItem(IDC_SHOWDET)->Invalidate(true);//ˢ�¿ؼ�
	//image1.Destroy();
	
	//ͼ���˲�ȥ�롢��Ե��⡢��ֵ��������
	cvtColor(srcImage, grayImage, CV_BGR2GRAY);//��ûҶ�ͼ��
    medianBlur(grayImage, grayImage, 5);//��ֵ�˲�
    Canny(grayImage, edgeImage, 125, 300);//Canny��Ե���  
    threshold(edgeImage,edgeImage,100,255,THRESH_BINARY);//��ֵ�ָ�õ���ֵͼ��
	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3)); //����
    dilate( edgeImage, dilateImg, element); 

	//�ⲿ�ӿ�  
    vector<vector<Point>> contours;  
    vector<Vec4i> hierarchy;  
    findContours( dilateImg, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);//����ⲿ����
	Mat contoursImage(srcImage);
	vector<Rect> r(contours.size());
	vector<int> a(contours.size());
	int i;
	for( i=0; i<contours.size(); i++)
	{
		r[i]=boundingRect(contours[i]);//�����Ӿ���
		a[i]=r[i].area();//����������ε��������������
	}
	vector<int>::iterator biggest = max_element(begin(a), end(a));
	i=distance(begin(a), biggest);//�������ⲿ���ε����� 
    rectangle(contoursImage, r[i], Scalar(255,255,255), 3);//���������Ӿ��ο� 

	//����grabCut������ͼ
	Mat bg,fg;
	Mat mask,res;
	mask.create( srcImage.size(), CV_8UC1);
    grabCut( srcImage, mask, r[i], bg, fg, 1, 0 );
    Mat binMask;
	getBinMask( mask, binMask );
    srcImage.copyTo( res, binMask );

	//����任
	Mat warp_mat( 2, 3, CV_32FC1 );
	Point2f srcTri[3];
    Point2f dstTri[3];
	dstImage=Mat::zeros( srcImage.rows, srcImage.cols, srcImage.type());

	srcTri[0] = Point2f( 0,0 );
	srcTri[1] = Point2f( srcImage.cols - 1, 0 );
	srcTri[2] = Point2f( 0, srcImage.rows - 1 );

	dstTri[0] = Point2f( srcImage.cols*0.0, srcImage.rows*0.33 );
	dstTri[1] = Point2f( srcImage.cols*0.85, srcImage.rows*0.25 );
	dstTri[2] = Point2f( srcImage.cols*0.15, srcImage.rows*0.7 );
	warp_mat = getAffineTransform( srcTri, dstTri );
	warpAffine( res, dstImage, warp_mat, dstImage.size() );

	imshow("result",dstImage);

	//��ʾ����ROI
 //   srcImage(r[i]).copyTo(dstImage);//��ȡ����ROI
	//MatToCImage(dstImage,image1);//Matת��ΪCImage
	//

 //   CRect rect;//��������� 
	//CRect rect1;
 //   int width = image1.GetWidth();//��ȡͼƬ���  
 //   int height = image1.GetHeight();//��ȡͼƬ�߶�  
 // 
 //   GetDlgItem(IDC_SHOWDET)->GetWindowRect(&rect);//�����ھ���ѡ�е�picture�ؼ���  
 //   ScreenToClient(&rect);//���ͻ���ѡ�е�Picture�ؼ���ʾ�ľ���������
 // 
 //   CWnd *pWnd=GetDlgItem(IDC_SHOWDET);//���pictrue�ؼ����ڵľ��  
 //   pWnd->GetClientRect(&rect);//���pictrue�ؼ����ڵľ�������  
 //   CDC *pDC=pWnd->GetDC();//���pictrue�ؼ���DC 
	////SetStretchBltMode(pDC->m_hDC,STRETCH_HALFTONE); 
 //   //image.StretchBlt(pDC->m_hDC,rect,SRCCOPY); 

	//if(width<=rect.Width() && height<=rect.Width()) //���ͼƬ�ĳߴ�С��ͼƬ�ؼ��ߴ磬��������ʾ  
 //   {  
 //       rect1 = CRect(rect.TopLeft(), CSize(width,height));  
	//	SetStretchBltMode(pDC->m_hDC,STRETCH_HALFTONE); 
 //       image1.StretchBlt(pDC->m_hDC,rect1,SRCCOPY); 
 //   }  
 //   else//���ͼƬ�ĳߴ����ͼƬ�ؼ��ĳߴ�  
 //   {  
 //       float xScale=(float)rect.Width()/(float)width;//��X�������������  
 //       float yScale=(float)rect.Height()/(float)height;//��Y�������������  
 //       float ScaleIndex=(xScale<=yScale?xScale:yScale);  
 //       rect1 = CRect(rect.TopLeft(), CSize((int)width*ScaleIndex,(int)height*ScaleIndex)); 
	//	SetStretchBltMode(pDC->m_hDC,STRETCH_HALFTONE); 
 //       image1.StretchBlt(pDC->m_hDC,rect1,SRCCOPY); 
 //   }  
 //   ReleaseDC(pDC);//�ͷ�picture�ؼ���DC

}

