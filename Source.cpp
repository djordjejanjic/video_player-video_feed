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
	} while (x < 0 || x > 1);
	getchar();

	return x;
}

char* user() {
	char user[20];

	printf("Upisite Vas user_name (ex: my user_name is djord in C:\\Users\\djord\\): ");
	scanf("%[^\n]", user);
	getchar();
	printf("\n");

	return user;
}

//Funkcija za biranje videa koji korisnik zeli da pokrene
char* browse() {
	char string[30];
	
	printf("Upisite naziv Vaseg videa | ex: video.mp4 (video se mora nalaziti na dekstopu): ");
	scanf("%[^\n]", string);
	getchar();
	printf("\n");
	printf("Otvorili ste video: %s\n\n", string);
	
	return string;
}

int generateVideo() {
	int option = prompt();
	char string[30];
	char string1[100] = "C:\\Users\\";
	char *location = "\\Desktop\\";

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
			cv::imshow("Web_cam in C++", frejmovi);

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
		//Spajanje string1 promenljive sa upisanim korisnickim imenom od strane korisnika i onda spajanje Desktop lokacije sa datim korisnickim imenom
		strcat(string1, user());
		strcat(string1, location);

		//Kopiranje stringa iz funkcije browse() u lokalni string
		strncpy(string, browse(), 30);

		//Spajanje lokalnog stringa i promenljive string1 koja sadrzi putanju do Dekstopa
		strcat(string1, string);

		cv::VideoCapture video(string1);

		double sirina = video.get(cv::CAP_PROP_FRAME_WIDTH);
		double visina = video.get(cv::CAP_PROP_FRAME_HEIGHT);

		//Postavljanje sirine i visine videa tako da visina dolazi do ivica ekrana, a sirina respektivno smanjena u odnosu na razmeru width X height
		video.set(cv::CAP_PROP_FRAME_WIDTH, 800 * (sirina / visina));
		video.set(cv::CAP_PROP_FRAME_HEIGHT, 800);

		//Proveravanje da li je video otvoren
		if (!video.isOpened()) return -1;

		//Cuvanje frejmova
		cv::Mat frejmovi;

		while (video.read(frejmovi))
		{
			resize(frejmovi, frejmovi, cv::Size(800 * (sirina / visina), 800), 0, 0, cv::INTER_CUBIC);
			cv::namedWindow("Video player in C++", cv::WINDOW_AUTOSIZE);
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

int main()
{
	generateVideo();

	return 0;
}