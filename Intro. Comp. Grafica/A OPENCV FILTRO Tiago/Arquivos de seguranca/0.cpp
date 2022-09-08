/*Tiago*/
/*Pra compilar no linux com o opencv 4, só tirar o "local" do path tanto do eigen quanto do que o
professor pediu pra implementar e também no opencv 4 os comandos CV_BGR2HSV e CV_BGR2GRAY foram substituidos
por COLOR_BGR2HSV e COLOR_BGR2GRAY*/

#include <iostream>
#include <fstream>
#include <string>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>


using namespace std;
using namespace cv;

////</
int blur_element = 0;
////>/



Mat destino;
string	filename;	// Image file name

Mat erosion_dst, dilation_dst;
int erosion_elem = 2; /*Element:    0 = Rect     1 = Cross     2 = Ellipse    */ 
/* Kernel size: 2n +1 */
int erosion_size = 21;
int dilation_elem = 2; /*Element:    0 = Rect     1 = Cross     2 = Ellipse    */ 
int dilation_size = 21;

Mat destino_gray_Lpla, dst_Lpla;

    int kernel_size_Laplacian = 3;
    int scale_Laplacian = 1;
    int delta_Laplacian = 0;
    int ddepth = CV_16S;

/*Prototipos de funções*/
//void blurF (int, void* ); Formato que o createTrackbar aceita

void chamarSobelF (int, void* ); //preciasmos disso por causa da forma que Sobel é escrita. Com os args da main
int sobelF_real (int , char** ); //preciasmos disso por causa da forma que Sobel é escrita. Com os args da main
int xargc; char** xargv; //vamos pegar as 2 da main

//max_elem = 2 (0,1,2); em ambos: erosion_elem e dilation_elem
//max_kernel_size = 21; em ambos: erosion_size e dilation_size
void Erosion( int, void* );
void Dilation( int, void* );

void Laplacian_Funcao();

int main(int argc, char** argv );
void avg ();

//Vecs para a função avg (média e desvio padrão)
template <class T>

Vec3d getAverage(Mat image){
int      h,w;
Vec3d    sum,pixel;

   h = image.rows;
   w = image.cols;

  	sum[0] = sum[1] = sum[2] = 0.0;
  
	if ( is_same<T, uchar>::value ){
 		for (int r = 0; r < h; r++)
  			for ( int c = 0; c < w; c++)
   			sum[0] += image.at<uchar>(r,c);
	} else {
		if (( is_same<T, Vec3b>::value ) || ( is_same<T, Vec3d>::value )){
 			for (int r = 0; r < h; r++)
  				for ( int c = 0; c < w; c++){
   				pixel = image.at<T>(r,c);
					sum[0] += pixel[0];
					sum[1] += pixel[1];
					sum[2] += pixel[2];
				}
		}
	}
 	sum[0] = sum[0] / ( h * w);
	if ( !is_same<T, uchar>::value ){
 		sum[1] = sum[1] / ( h * w);
 		sum[2] = sum[2] / ( h * w);
	}

   return sum;

}

template <class T>

Vec3d getStdDeviation(Mat image){
int      h,w;
Vec3d		sum, mean, pixel, ret;

   h = image.rows;
   w = image.cols;

  	sum[0] = sum[1] = sum[2] = 0.0;
  
 	mean = getAverage<T>(image);
	if ( is_same<T, Vec3b>::value ){
 		for (int r = 0; r < h; r++)
  			for ( int c = 0; c < w; c++){
   			pixel = image.at<Vec3b>(r,c);
   			ret = (pixel - mean );
   			sum[0] = sum[0]+ (ret[0] * ret[0]);
   			sum[1] = sum[1] + (ret[1] * ret[1]);
   			sum[2] = sum[2] + (ret[2] * ret[2]);
			}
 			ret = sum / (( h * w) * 1.0);  
			ret[0] = sqrt(ret[0]);
			ret[1] = sqrt(ret[1]);
			ret[2] = sqrt(ret[2]);
	} else {
		if ( is_same<T, Vec3d>::value ){
 			for (int r = 0; r < h; r++)
  				for ( int c = 0; c < w; c++){
   				pixel = image.at<Vec3d>(r,c);
   				ret = (pixel - mean );
   				sum[0] = sum[0] + (ret[0] * ret[0]);
   				sum[1] = sum[1] + (ret[1] * ret[1]);
   				sum[2] = sum[2] + (ret[2] * ret[2]);
				}
 				ret = sum / (( h * w) * 1.0);  
				ret[0] = sqrt(ret[0]);
				ret[1] = sqrt(ret[1]);
				ret[2] = sqrt(ret[2]);
		} else {
 			for (int r = 0; r < h; r++)
  				for ( int c = 0; c < w; c++){
   				pixel[0] = image.at<uchar>(r,c);
   				ret[0] = (pixel[0] - mean[0] );
   				sum[0] = sum[0] + (ret[0] * ret[0]);
				}
 				ret[0] = sum[0] / (( h * w) * 1.0);  
				ret[0] = sqrt(ret[0]);
		}
	}
   return ret;

}

Mat		image;		// Image object

int main(int argc, char** argv ) {
	xargc = argc; //vamos pegar da main
	xargv = argv; //vamos pegar da main
	
	


	filename = "../imagens/imagem_01.jpg";

	// Read image from disk
	image = imread(filename);
	destino =  imread(filename); //defini já q no comeco, destimo é igua a imagem carregada

	// Check if image was loaded
	if ( image.empty() ){
		cerr << "Image [ " << filename << " ] not found!" << endl;
		cerr << "Quitting!" << endl;
		exit (-1);
	}

    // Provided by OpenCV function bilateralFilter() We use 5 arguments:
    // src: Source image
    // dst: Destination image
    // d: The diameter of each pixel neighborhood.
	// Standard deviation in the color space.
	// Standard deviation in the coordinate space (in pixel terms).

	//NO CASO DO BILATERAL, VOCÊ TEM QUE POR OUTRO OBJETO MAT DE SAÍDA! NÃO PODE SER O MESMO
	//Q O DE ENTRADA
	
	imshow( "Img Original", image ); //Mostrar img destino em uma janela nomeada "Original"]

	//----------------------- CHAMANDO AS FUNÇÕES -----------------------------
	//Começa os filtros:

	/*--------------------------<<<<<<<<<<<<*/
	cout << "Preencha com os valores do Filtro Bilateral: \n";
	bilateralFilter ( image, destino, 15, 95, 45 );
	imshow( "Filtro Bilateral (1)", destino );

	
	cout << "Preencha com os valores de Blur: \n";
	blur(destino,destino,Size(10,10));
	imshow( "blur", destino );

	cout << "Preencha com os valores de Sobel: \n";
	chamarSobelF (0,0);
	
	cout << "Preencha com os valores de GaussianBlur: \n";
	GaussianBlur(destino, destino, Size(3, 3), 0);
	imshow( "GaussianBlur", destino );
	//^Ela já chama uma janela

	cout << "Preencha com os valores de Laplacian: \n";
	Laplacian_Funcao ();
	

	cout << "Preencha com os valores de Erode: \n";
	namedWindow( "Erosion Demo", WINDOW_AUTOSIZE );
	Erosion( 0, 0 );

	cout << "Preencha com os valores de Dilate: \n";
	namedWindow( "Dilation Demo", WINDOW_AUTOSIZE );
	Dilation( 0, 0 );
	

	cout << "Converter para HSV? 0:Não 1:Sim \n";
	cvtColor(image, destino, COLOR_BGR2GRAY) ; //para HSV (ou cv_BGR2GRAY)
	imshow( "COLOR_BGR2GRAY", destino );
	
	cout << "Converter para HSV? 0:Não 1:Sim \n";
	cvtColor(image, destino, COLOR_BGR2HSV) ; //para HSV (ou cv_BGR2HSV)
	imshow( "COLOR_BGR2HSV", destino );

	
	avg ();//MEdia e Desvio padrão
	cout << "Salvando Imagem \n";
	imwrite("../imagens/ImagemFinal.jpg", destino);
	//SALVA NESSE ENDEREÇO ^

	waitKey(0);			// Wait for any key was pressed and return
							// the key code pressed or -1 if no key pressed
							// Parameter
							// =0 - Wait for until key pressed
							// >0 - Wait by N miliseconds and return
	return 0;

}
//Criar uma janela pra mostrar
	//namedWindow( filename.c_str(), WINDOW_NORMAL); e...
	//namedWindow( "Filtro Bilateral", WINDOW_NORMAL ); //Temos que por isso aqui pra fazer a janela com o botão deslizante
	// ^ Por o nome da janela a esquerda "Janela"
	//moveWindow( "Filtro Bilateral", image.cols, 0 );
	//destroyWindow("Filtro Bilateral"); USAR PARA FECHAR CADA JANELA


/* -----------------------------------  NÃO-EXCLUIR: NOMES DAS JANELAS --------------------------------------

Sobel ✓
Blur ✓
Erode ✓
Dilate ✓
G. / GaussianBlur ✓
Laplacian ✓
Filtro Bilateral ✓
---> para HSV ✓
para Tons de cinza ✓

Calcular a media
Calcular o desvio padrão

Salvar a imagem
	 
	 -----------------------------------  NÃO-EXCLUIR: NOMES DAS JANELAS --------------------------------------
*/

int sobelF_real (int argc, char** argv)
{
  
  cv::CommandLineParser parser(argc, argv,
                               "{@input   |../imagens/imagem_01.jpg|input image}" //Local da imagem
                               "{ksize   k|1|ksize (hit 'K' to increase its value at run time)}"
                               "{scale   s|1|scale (hit 'S' to increase its value at run time)}"
                               "{delta   d|0|delta (hit 'D' to increase its value at run time)}"
                               "{help    h|false|show help message}");

  /*
  cout << "The sample uses Sobel or Scharr OpenCV functions for edge detection\n\n";
  parser.printMessage();
  cout << "\nPress 'ESC' to exit program.\nPress 'R' to reset values ( ksize will be -1 equal to Scharr function )";
  */
 
  //![variables]
  // First we declare the variables we are going to use
  Mat image,src, src_gray;
  Mat grad;
  const String window_name = "Sobel Demo - Simple Edge Detector";
  int ksize = parser.get<int>("ksize");
  int scale = parser.get<int>("scale");
  int delta = parser.get<int>("delta");
  int ddepth = CV_16S;
  //![variables]

  //![load]
  String imageName = parser.get<String>("@input");
  // As usual we load our source image (src)
  image = imread( samples::findFile( imageName ), IMREAD_COLOR ); // Load an image

  // Check if image is loaded fine
  if( image.empty() )
  {
    printf("Error opening image: %s\n", imageName.c_str());
    return EXIT_FAILURE;
  }
  //![load]

 
    //![reduce_noise]
    // Remove noise by blurring with a Gaussian filter ( kernel size = 3 )
    GaussianBlur(image, src, Size(3, 3), 0, 0, BORDER_DEFAULT);
    //![reduce_noise]

    //![convert_to_gray]
    // Convert the image to grayscale
    cvtColor(src, src_gray, COLOR_BGR2GRAY);
    //![convert_to_gray]

    //![sobel]
    /// Generate grad_x and grad_y
    Mat grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y;

    /// Gradient X
    Sobel(src_gray, grad_x, ddepth, 1, 0, ksize, scale, delta, BORDER_DEFAULT);

    /// Gradient Y
    Sobel(src_gray, grad_y, ddepth, 0, 1, ksize, scale, delta, BORDER_DEFAULT);
    //![sobel]

    //![convert]
    // converting back to CV_8U
    convertScaleAbs(grad_x, abs_grad_x);
    convertScaleAbs(grad_y, abs_grad_y);
    //![convert]

    //![blend]
    /// Total Gradient (approximate)
    addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);
    //![blend]

    //![display]
    imshow(window_name, grad);

	/*---------------ADICIONAR UM ENTRE COM O PARâMETRO----------------
	scale =  1;
    ksize = -1;
    delta =  0;
	*/

	//Mudando parâmetros pelo teclado

	/*
    char key = (char)waitKey(0);
    //![display]

    if(key == 27)
    {
      return EXIT_SUCCESS;
    }

    if (key == 'k' || key == 'K')
    {
      ksize = ksize < 30 ? ksize+2 : -1;
    }

    if (key == 's' || key == 'S')
    {
      scale++;
    }

    if (key == 'd' || key == 'D')
    {
      delta++;
    }

    if (key == 'r' || key == 'R')
    {
      scale =  1;
      ksize = -1;
      delta =  0;
    }
	*/
  
  return EXIT_SUCCESS;
}



void chamarSobelF (int, void* ){
  sobelF_real (xargc, xargv );//PRECISA DE PASSAR ESSES ARGs, que pegamos da main, através do escopo da main, copiando os para essas 2 variáveis
}

/*
void blurF (int, void* ){ //Formato que a função createTrackbar aceita para sua função que será chamada no último argumento
		
		
		///
	  int valor = 1; //NO CASO DO blur, aqui nao pode ter 0 "zero"
	  destino = imread(filename); //ZERANDO DESTINO, PRA APLICARMOS CERTO/REFAZER/FAZER MENOS QUE

  if( blur_element == 0 ){ valor = 1;} //o if recebe o valor do createTrackbar (...&blur_element )
  else if( blur_element == 1 ){ valor = 45; }
  else if( blur_element == 2) { valor = 95; } //VAI ABRIR A IMAGEM, PARA "DESFAZER", OU SEJA, APLICAR A ORIGINAL
//PARA DESFAZER TEM Q EXISTIR UM OUTRO MAT, GUARDANDO O Q FOI FEITO.
  //_______>>>>>>> ELE SÓ NÃO CONSEGUE "DESFAZER " O BLUR. DESCUBRA COMO Q FAZ PARA VOLTAR AO ORIGINAL, A FUNÇÃO

	// int element = ;
		///

		
		//criar variavel, para o primeiro argumento
		//blur(image,image,Size(30,15)); //subir dps?
		
		
	// Show our image inside it.
		blur(destino,destino,Size(valor,valor)); //subir dps? //NAO MODIFICAR A ORIGINAL
		imshow( filename.c_str(), destino ); //OK, FUNCIONA
		
	}
*/

//!// Variáveis de alteração de Erosion:  erosion_elem e erosion_size 
void Erosion( int, void* )
{
  int erosion_type = 0;
  if( erosion_elem == 0 ){ erosion_type = MORPH_RECT; }
  else if( erosion_elem == 1 ){ erosion_type = MORPH_CROSS; }
  else if( erosion_elem == 2) { erosion_type = MORPH_ELLIPSE; }
  Mat element = getStructuringElement( erosion_type,
                       Size( 2*erosion_size + 1, 2*erosion_size+1 ),
                       Point( erosion_size, erosion_size ) );
  erode( destino, erosion_dst, element );
  imshow( "Erosion Demo", erosion_dst );
}

//!// Variáveis de alteração de Dilation:  dilation_elem e dilation_size 
void Dilation( int, void* )
{
  int dilation_type = 0;
  if( dilation_elem == 0 ){ dilation_type = MORPH_RECT; }
  else if( dilation_elem == 1 ){ dilation_type = MORPH_CROSS; }
  else if( dilation_elem == 2) { dilation_type = MORPH_ELLIPSE; }
  Mat element = getStructuringElement( dilation_type,
                       Size( 2*dilation_size + 1, 2*dilation_size+1 ),
                       Point( dilation_size, dilation_size ) );
  dilate( destino, dilation_dst, element );
  imshow( "Dilation Demo", dilation_dst );
}

void Laplacian_Funcao () {
    // Reduce noise by blurring with a Gaussian filter ( kernel size = 3 )
    GaussianBlur( destino, destino, Size(3, 3), 0, 0, BORDER_DEFAULT );
    cvtColor( destino, destino_gray_Lpla, COLOR_BGR2GRAY ); // Convert the image to grayscale_Laplacian
    Mat abs_dst_Lpla;
    Laplacian( destino_gray_Lpla, dst_Lpla, ddepth, kernel_size_Laplacian, scale_Laplacian, delta_Laplacian, BORDER_DEFAULT );
    // converting back to CV_8U
    convertScaleAbs( dst_Lpla, abs_dst_Lpla );
    imshow( "Laplace", abs_dst_Lpla );
}

void avg () {
	Mat 		cimage;
string	filename2;	// Image file name

	//filename2 = "../imagens/teste.png";
	filename2 = "../imagens/imagem_01.jpg"; //ou a "teste.png"

	// Read image from disk
	image = imread(filename2);

	// Check if image was loaded
	if ( image.empty() ){
		cerr << "Image [ " << filename2 << " ] not found!" << endl;
		cerr << "Quitting!" << endl;
		exit (-1);
	}
	
	cout << "1> Media = " << getAverage<Vec3b>(image) << endl;
	cout << "1> Media = " << getAverage<uchar>(image) << endl;

	cout << "2> Media = " << getAverage<Vec3b>(image) << endl;
	cout << "2> Media = " << getAverage<uchar>(image) << endl;

	cout << "Desvio padrao = " << getStdDeviation<Vec3b>(image) << endl;
	cout << "Desvio padrao = " << getStdDeviation<uchar>(image) << endl;

   cvtColor(image, cimage, COLOR_BGR2GRAY);
	cimage.convertTo(cimage, CV_8UC1);

	cout << "Media = " << getAverage<uchar>(cimage) << endl;
	cout << "Media = " << getAverage<uchar>(cimage) << endl;

	cout << "2> Media = " << getAverage<Vec3b>(cimage) << endl;
	cout << "2> Media = " << getAverage<uchar>(cimage) << endl;

	cout << "Desvio Padrao = " << getStdDeviation<uchar>(cimage) << endl;
	cout << "Desvio Padrao = " << getStdDeviation<uchar>(cimage) << endl;

	// Create a window for display.
	 //namedWindow( filename2.c_str(), WINDOW_NORMAL); 
	// Show our image inside it.
	 //imshow( filename2.c_str(), image );   
}