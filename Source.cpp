#define _CRT_SECURE_NO_WARNINGS

#include "opencv2\opencv.hpp";
#include "opencv2\highgui.hpp";
#include <stdio.h>;
#include <stdlib.h>;

//Funkcija za biranje da li korisnik zeli da pokrene video ili web kameru
int prompt() {
	int x;
	
	do {
		printf("Da li zelite da pokrenete video ili web cameru (1 - video, 0 - web camera): ");
		scanf("%d", &x);
	} while (getchar() != '\n' && x != 0 && x != 1);

	return x;
}

//Funkcija za biranje videa koji korisnik zeli da pokrene
char* browse() {
	char string[30];
	
	printf("Upisite lokaciju Vaseg videa | ex: video.mp4 (video se mora nalaziti na dekstopu): ");
	scanf("%[^\n]", string);
	printf("\n");
	printf("Otvorili ste video: %s\n\n", string);
	
	return string;
}

int main()
{
	int option = prompt();
	char string[30];
	char string1[100]= "C:\\Users\\djord\\Desktop\\";
	
	printf("\n");

	//Kreiranje objekta za video
	if (option == 0) {
		
		cv::VideoCapture video(0);

		//Proveravanje da li je video otvoren
		if (!video.isOpened()) return -1;

		//Cuvanje frejmova
		cv::Mat frejmovi;

		//Rezolucija videa
		//Prilagodjenu velicini videa
		int sirinaFrejma = video.get(cv::CAP_PROP_FRAME_WIDTH);
		int visinaFrejma = video.get(cv::CAP_PROP_FRAME_HEIGHT);

		//Kreiranje writer objekta i snimanje web feed-a pod nazivom "output.avi"
		cv::VideoWriter output("output.avi", cv::VideoWriter::fourcc('M', 'P', '4', '2'), 10, cv::Size(sirinaFrejma, visinaFrejma));

		while (video.read(frejmovi))
		{
			//Prikaz frejmova
			cv::imshow("Video player in C++", frejmovi);

			//Ispisi frejm
			output.write(frejmovi);

			//Cekanje 25ms
			if (cv::waitKey(5) > 0)
			{
				break;
			}
		}
		output.release();
		video.release();
	}
	else 
	{
		//Kopiranje stringa iz funkcije browse() u lokalni string
		strncpy(string, browse(), 30);

		//Spajanje lokalnog stringa i promenljive string1 koja sadrzi putanju do Dekstopa
		strcat(string1, string);

		cv::VideoCapture video(string1);
		
		int sirina = video.get(cv::CAP_PROP_FRAME_WIDTH);
		int visina = video.get(cv::CAP_PROP_FRAME_HEIGHT);

		video.set(cv::CAP_PROP_FRAME_WIDTH, sirina/2);
		video.set(cv::CAP_PROP_FRAME_HEIGHT, visina/2);

		//Proveravanje da li je video otvoren
		if (!video.isOpened()) return -1;

		//Cuvanje frejmova
		cv::Mat frejmovi;

		while (video.read(frejmovi))
		{
			resize(frejmovi, frejmovi, cv::Size(sirina/2, visina/2), 0, 0, cv::INTER_CUBIC);
			cv::namedWindow("Video player in C++", 1);
			//Prikaz frejmova
			cv::imshow("Video player in C++", frejmovi);

			//Cekanje 25ms
			if (cv::waitKey(5) > 0)
			{
				break;
			}
		}
		video.release();
	}	

	cv::destroyAllWindows();

	return 0;
}