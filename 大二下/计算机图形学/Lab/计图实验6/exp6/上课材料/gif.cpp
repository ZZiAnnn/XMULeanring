#include <Eigen/Core>
#include <cstdlib>
#include "ppm.hpp"
#include "camera.hpp"
#include "raytracer.hpp"
#include "opencv2/opencv.hpp"
#include <windows.h>
#include <vector>
#include <iostream>
#include <Magick++.h>
using namespace Magick;
using namespace std;
using namespace cv;
int num_samples = 2;

void building_frame(float h, int ii)
{
	char frampath[60];
	int width = 400, height = 300;

	PPM outrlt(width, height);
	PPM inrlt(width, height);
	Camera cam;
	Scene world;
	Sphere sp1(Vector3f(0, h, -2), 1.0);//���Ļ�ɫС��
	Sphere sp2(Vector3f(0, -10000.5, -2), 10000.0);
	Sphere sp3(Vector3f(-2.0, 0, -2), 0.5);
	Sphere sp4(Vector3f(1.0, -0.2, -1.0), 0.3);
	Sphere sp5(Vector3f(3.0, 0, -2.2), 0.4);
	Sphere sp6(Vector3f(-1, 0.0, -0.8), 0.2);

	Material mtl, mtl2, mtl3, mtl4, mtl5;//mLx
	mtl.SetKa(Vector3f(0.5, 0.5, 0.5));//���Ļ�ɫС��
	mtl.SetKd(Vector3f(0.8, 0.6, 0.0));
	mtl.SetKs(Vector3f(0.7, 0.8, 0.8));
	mtl.SetTransparent(false);
	mtl.SetReflective(true);
	mtl.SetShiness(50);

	mtl2.SetKa(Vector3f(0.5, 0.5, 0.5));//Ӧ���ǿ�������
	mtl2.SetKd(Vector3f(0.0, 0.6, 0.2));
	mtl2.SetKs(Vector3f(0.1, 1.0, 0.8));
	mtl2.SetTransparent(false);
	mtl2.SetReflective(false);
	mtl2.SetShiness(10);

	mtl3.SetKa(Vector3f(0.5, 0.5, 0.5));//��ɫС��
	mtl3.SetKd(Vector3f(0.0, 0.3, 0.6));
	mtl3.SetKs(Vector3f(0.0, 0.0, 0.0));
	mtl3.SetTransparent(false);
	mtl3.SetReflective(false);
	mtl3.SetShiness(10);

	mtl4.SetKa(Vector3f(0.1, 0.1, 0.1));//�Ҳ��ɫС��
	mtl4.SetKd(Vector3f(0.0, 0.0, 0.0));
	mtl4.SetKs(Vector3f(0.0, 0.0, 0.0));
	mtl4.SetTransparent(true);
	mtl4.SetReflective(false);
	mtl4.SetRefraction(1.33);
	mtl4.SetShiness(200);

	mtl5.SetKa(Vector3f(0.5, 0.5, 0.5));//�Ҳ��ɫС��
	mtl5.SetKd(Vector3f(0.75, 0.56, 0.0));
	mtl5.SetKs(Vector3f(0.75, 0.56, 0.0));
	mtl5.SetTransparent(false);
	mtl5.SetReflective(false);
	mtl5.SetRefraction(1.33);
	mtl5.SetShiness(100);

	world.Insert(make_pair(sp1, mtl));
	world.Insert(make_pair(sp2, mtl2));
	world.Insert(make_pair(sp3, mtl3));
	world.Insert(make_pair(sp4, mtl4));
	world.Insert(make_pair(sp5, mtl5));
	// ���ļ�
	FILE* fp = NULL;	int r, g, b;

	if (ii > 3)//�ļ����ڶ���3��ͼƬ
	{
		char path[60];
		sprintf(path, "./Frame//frame%d.ppm", ii - 1);
		fopen_s(&fp, path, "rb");
		if (fp == NULL) {
			printf("Error: failed to open file %s\n", path);
			return;
		}

		// ��ȡ PPM �ļ�ͷ��Ϣ
		char header[64];
		fgets(header, 64, fp);  // �ļ�����
		if (header[0] != 'P') {
			printf("Error: invalid PPM file format :%s\n", header);

			fclose(fp);
			return;
		}
		fgets(header, 64, fp);  // ͼ������߶�


		sscanf_s(header, "%d %d", &width, &height);// cout << "w" << " h  " << width << " " << height << endl;
		fgets(header, 64, fp);  // �������ֵ
	}
	//���˶�ģ��
	for (int j = height - 1; j >= 0; --j)
	{
		for (int i = 0; i < width; ++i)
		{
			if (ii > 3)
			{
				char get[40];
				fgets(get, 40, fp);
				sscanf_s(get, "%d %d %d", &r, &g, &b);
				get[0] = '\0';
			}
			//��ʼ��ÿ������
			bool test = false;
			//���ɹ���
			Vector3f color;
			float u = (i) / (float)(width);
			float v = (j) / (float)(height);
			Ray ray = cam.GenerateRay(u, v);


			color = RayColor(ray, world, test);

			if (ii > 3)//�ļ����ڶ���3��ͼƬ
			{
				if (r != color[0] || g != color[1] || b != color[2])
				{
					color[0] = int(255.99 * color[0]) * 0.7 + r * 0.3;
					color[1] = int(255.99 * color[1]) * 0.7 + g * 0.3;
					color[2] = int(255.99 * color[2]) * 0.7 + b * 0.3;
				}

				//cout << "  i" << i << "  j" << j;// << "  color   " << color[0] << " " << color[1] << " " << color[2] << endl;
					//cout << "i" << i << "  j" << j << "  rgb" << r <<" " << g <<" " << b << endl;
				//	cout << "  colorrgb  " << color[0] <<" " << color[1]<<" " << color[2] << endl;

			}
			else
			{
				color[0] = int(255.99 * color[0]);
				color[1] = int(255.99 * color[1]);
				color[2] = int(255.99 * color[2]);
			}
			outrlt.SetPixel(j, i, (int)color[0], (int)color[1], (int)color[2]);
		}
	}
	if (ii > 3)
	{
		fclose(fp);
	}
	sprintf(frampath, "./Frame//frame%d.ppm", ii);
	outrlt.Write2File(frampath);
}

int main()
{
	system("md Frame");//���ļ���
	int n = 100;/////////////////////////////////////
	int count = 0;
	float h = 2.5f, g = -0.0098f, v = 0, x = 0;
	for (int i = 0; i <= n; ++i)
	{
		if (count <= 5)//��ײ����
		{
			v += g;
			x += v;

			if (x + h <= 0.67)
			{
				v = -0.82 * v;
				count++;
			}
		}
		building_frame(x + h, i);//��������һ��һ��֡����
	}
	cout << "all finished ��" << endl;

	vector<Image> frames;

	for (int i = 0; i < n; i++)
	{
		char fpath[60];
		sprintf(fpath, "Frame//frame%d.ppm", i);
		cout << "fpath finished ��" << fpath << endl;
		Image image(fpath);
		cout << "image(fpath) finished ��" << endl;
		frames.push_back(image);
	}
	cout << "push_back finished ��" << endl;
	/*��֮ǰ���ɵ�һϵ�� PPM ��ʽ��ͼ������ڴ棬���浽һ�� vector �����У�����ʹ�� Image ������װÿ��ͼ��
	���У�sprintf �����ǽ��ַ�������ָ����ʽ��ϳ��µ��ַ�������������� "Frame//"��"frame"��i��".ppm" ���ĸ�����
	�������µ��ַ��� framepath�����ļ�����Ȼ��ͨ�� Image ��Ĺ��캯������ͼ������ڴ沢���浽 frames ������
	�����տ���ͨ������ frames ����������ϳ�Ϊһ�� GIF ����*/
	for (int i = 0; i < frames.size(); i++) {
		frames[i].animationDelay(5);
	}
	cout << "animationDela finished ��" << endl;
	/*����ÿ��֡�ڶ����г�����ʱ�䡣����ÿ�� Image ����󣬵��� animationDelay() ����������һ��������ʾ�ӳٵĺ�������
	�������ͨ������ GIF ���������Կ���ÿ֮֡���ʱ�������Ӷ����������Ĳ����ٶȡ�*/
	string output_file = "output.gif";
	writeImages(frames.begin(), frames.end(), output_file);
	system("rd /s /q Frame");
	/*��һ�δ���������ǽ�֮ǰ�����ڴ��ͼ��ϳ�Ϊһ�� GIF ������
	������д�뵽��Ϊ "output.gif" ���ļ��С����У�writeImages() ������ Magick++ ���ṩ�ĺ�����
	����������������frames.begin() �� frames.end() ����������������ʾҪд���ͼƬ��Χ��output_file ��ʾ������ļ�����
	writeImages() �������Զ������ļ����ĺ�׺���ж�������ļ���ʽ������ĺ�׺Ϊ .gif������������һ�� GIF ������
	ʹ�ñ�׼�⺯�� system() ����ϵͳ���ɾ��������ɵ� PPM ͼ����ļ��� Frame��*/
	return 0;
}