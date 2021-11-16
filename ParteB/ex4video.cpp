#include <iostream>

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char **argv){
    if(argc != 3){
        puts("please give input and output file:");
        puts("Usage: ./bin/ex4video <input_file> <output_file>");
		exit (1);
    }
    VideoCapture vid(argv[1]);
    if(!vid.isOpened()){
		cout << "Error opening input video file: " << argv[1] << " " << endl;
	}else{
        // get vid info
        int fps = vid.get(5);
        int frame_width = static_cast<int>(vid.get(3));
        int frame_height = static_cast<int>(vid.get(4));
        Size frame_size(frame_width, frame_height);
        VideoWriter vid_out(argv[2], VideoWriter::fourcc('a','v','c','1'), fps, frame_size);
        
        puts("press q ou ESC to stop frame by frame display...");
        while(vid.isOpened()){
            Mat frame;
            bool success = vid.read(frame);     // ler frame by frame
            if (success){
                imshow("frame by frame", frame);
                vid_out.write(frame);   // escrever frame no objecto de destino
            }else{
                break;
            }
            int key = waitKey(30);      // each frame is displayed every 30ms
            if(key == 'q' || key == 27){
                cout << "stoped!" << endl;
                break;
            }
        }
        vid.release();
        vid_out.release();
        destroyAllWindows();
    }
    return 0;
}

