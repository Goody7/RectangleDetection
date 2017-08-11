
// Task6Dlg.cpp : 实现文件
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


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CTask6Dlg 对话框




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


// CTask6Dlg 消息处理程序

BOOL CTask6Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTask6Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTask6Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

CImage image,image1; //创建图片类 
void CTask6Dlg::OnBnClickedOpenButton()
{
	// TODO: 在此添加控件通知处理程序代码
	// 设置过滤器   
    TCHAR szFilter[] = _T("Image files(*.png; *.jpg;*.bmp)|*.png;*.jpg;*.bmp|All files(*.*)|*.*||");   
    // 构造打开文件对话框   
    CFileDialog fileDlg(TRUE,NULL,NULL,OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST|OFN_READONLY, szFilter, NULL);   
    CString strFilePath; 

	GetDlgItem(IDC_SHOWOP)->Invalidate(true);//刷新控件
	image.Destroy();

	//显示图片
	if (IDOK == fileDlg.DoModal())   
    { 
       // 如果点击了文件对话框上的“打开”按钮，则将选择的图片显示到图片控件中   
       strFilePath = fileDlg.GetPathName(); 
       image.Load(strFilePath); //根据图片路径加载图片  
       CRect rect;//定义矩形类 
	   CRect rect1;
       int width = image.GetWidth();//获取图片宽度  
       int height = image.GetHeight();//获取图片高度  
  
       GetDlgItem(IDC_SHOWOP)->GetWindowRect(&rect);//将窗口矩形选中到picture控件上  
       ScreenToClient(&rect);//将客户区选中到Picture控件表示的矩形区域内
  
       CWnd *pWnd=GetDlgItem(IDC_SHOWOP);//获得pictrue控件窗口的句柄  
       pWnd->GetClientRect(&rect);//获得pictrue控件所在的矩形区域  
       CDC *pDC=pWnd->GetDC();//获得pictrue控件的DC 
	   //SetStretchBltMode(pDC->m_hDC,STRETCH_HALFTONE); 
       //image.StretchBlt(pDC->m_hDC,rect,SRCCOPY); 

	   if(width<=rect.Width() && height<=rect.Width()) //如果图片的尺寸小于图片控件尺寸，则不缩放显示  
       {  
            rect1 = CRect(rect.TopLeft(), CSize(width,height));  
			SetStretchBltMode(pDC->m_hDC,STRETCH_HALFTONE); 
            image.StretchBlt(pDC->m_hDC,rect1,SRCCOPY); 
       }  
       else//如果图片的尺寸大于图片控件的尺寸  
       {  
            float xScale=(float)rect.Width()/(float)width;//求X方向的缩放因子  
            float yScale=(float)rect.Height()/(float)height;//求Y方向的缩放因子  
            float ScaleIndex=(xScale<=yScale?xScale:yScale);  
            rect1 = CRect(rect.TopLeft(), CSize((int)width*ScaleIndex,(int)height*ScaleIndex)); 
			SetStretchBltMode(pDC->m_hDC,STRETCH_HALFTONE); 
            image.StretchBlt(pDC->m_hDC,rect1,SRCCOPY); 
        }  
        ReleaseDC(pDC);//释放picture控件的DC 
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
  
  
    //重建cimage  
    cimage.Destroy();  
    cimage.Create(nWidth, nHeight, 8 * nChannels);  
  
  
    //拷贝数据  
  
  
    uchar* pucRow;                                  //指向数据区的行指针  
    uchar* pucImage = (uchar*)cimage.GetBits();     //指向数据区的指针  
    int nStep = cimage.GetPitch();                  //每行的字节数,注意这个返回值有正有负  
  
  
    if (1 == nChannels)                             //对于单通道的图像需要初始化调色板  
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
  
  
    //重建mat  
    if (1 == nChannels)  
    {  
        mat.create(nHeight, nWidth, CV_8UC1);  
    }  
    else if(3 == nChannels)  
    {  
        mat.create(nHeight, nWidth, CV_8UC3);  
    }  
  
  
    //拷贝数据  
  
  
    uchar* pucRow;                                  //指向数据区的行指针  
    uchar* pucImage = (uchar*)cimage.GetBits();     //指向数据区的指针  
    int nStep = cimage.GetPitch();                  //每行的字节数,注意这个返回值有正有负  
  
  
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
	// TODO: 在此添加控件通知处理程序代码
	Mat srcImage,dstImage,grayImage,edgeImage,dilateImg;
	CImageToMat(image, srcImage);//CImage转换为Mat
	//GetDlgItem(IDC_SHOWDET)->Invalidate(true);//刷新控件
	//image1.Destroy();
	
	//图像滤波去噪、边缘检测、二值化、膨胀
	cvtColor(srcImage, grayImage, CV_BGR2GRAY);//获得灰度图像
    medianBlur(grayImage, grayImage, 5);//中值滤波
    Canny(grayImage, edgeImage, 125, 300);//Canny边缘检测  
    threshold(edgeImage,edgeImage,100,255,THRESH_BINARY);//阈值分割得到二值图像
	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3)); //膨胀
    dilate( edgeImage, dilateImg, element); 

	//外部加框  
    vector<vector<Point>> contours;  
    vector<Vec4i> hierarchy;  
    findContours( dilateImg, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);//检测外部轮廓
	Mat contoursImage(srcImage);
	vector<Rect> r(contours.size());
	vector<int> a(contours.size());
	int i;
	for( i=0; i<contours.size(); i++)
	{
		r[i]=boundingRect(contours[i]);//获得外接矩形
		a[i]=r[i].area();//计算各个矩形的面积并存入容器
	}
	vector<int>::iterator biggest = max_element(begin(a), end(a));
	i=distance(begin(a), biggest);//获得最大外部矩形的索引 
    rectangle(contoursImage, r[i], Scalar(255,255,255), 3);//对外轮廓加矩形框 

	//利用grabCut函数抠图
	Mat bg,fg;
	Mat mask,res;
	mask.create( srcImage.size(), CV_8UC1);
    grabCut( srcImage, mask, r[i], bg, fg, 1, 0 );
    Mat binMask;
	getBinMask( mask, binMask );
    srcImage.copyTo( res, binMask );

	//仿射变换
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

	//显示矩形ROI
 //   srcImage(r[i]).copyTo(dstImage);//截取矩形ROI
	//MatToCImage(dstImage,image1);//Mat转换为CImage
	//

 //   CRect rect;//定义矩形类 
	//CRect rect1;
 //   int width = image1.GetWidth();//获取图片宽度  
 //   int height = image1.GetHeight();//获取图片高度  
 // 
 //   GetDlgItem(IDC_SHOWDET)->GetWindowRect(&rect);//将窗口矩形选中到picture控件上  
 //   ScreenToClient(&rect);//将客户区选中到Picture控件表示的矩形区域内
 // 
 //   CWnd *pWnd=GetDlgItem(IDC_SHOWDET);//获得pictrue控件窗口的句柄  
 //   pWnd->GetClientRect(&rect);//获得pictrue控件所在的矩形区域  
 //   CDC *pDC=pWnd->GetDC();//获得pictrue控件的DC 
	////SetStretchBltMode(pDC->m_hDC,STRETCH_HALFTONE); 
 //   //image.StretchBlt(pDC->m_hDC,rect,SRCCOPY); 

	//if(width<=rect.Width() && height<=rect.Width()) //如果图片的尺寸小于图片控件尺寸，则不缩放显示  
 //   {  
 //       rect1 = CRect(rect.TopLeft(), CSize(width,height));  
	//	SetStretchBltMode(pDC->m_hDC,STRETCH_HALFTONE); 
 //       image1.StretchBlt(pDC->m_hDC,rect1,SRCCOPY); 
 //   }  
 //   else//如果图片的尺寸大于图片控件的尺寸  
 //   {  
 //       float xScale=(float)rect.Width()/(float)width;//求X方向的缩放因子  
 //       float yScale=(float)rect.Height()/(float)height;//求Y方向的缩放因子  
 //       float ScaleIndex=(xScale<=yScale?xScale:yScale);  
 //       rect1 = CRect(rect.TopLeft(), CSize((int)width*ScaleIndex,(int)height*ScaleIndex)); 
	//	SetStretchBltMode(pDC->m_hDC,STRETCH_HALFTONE); 
 //       image1.StretchBlt(pDC->m_hDC,rect1,SRCCOPY); 
 //   }  
 //   ReleaseDC(pDC);//释放picture控件的DC

}

