function [] = lab2()

% ��ȡԭ�Ҷ�ͼ
R = imread('Einstein.tif');

% ֱ��ͼ���⻯
S = histeq(R);

figure(1)
% uint8�������Ѳ���ת��Ϊ�޷�����
subplot(121),imshow(uint8(R)),title('ԭʼͼ��');
subplot(122),imshow(uint8(S)),title('ֱ��ͼ������ͼ��');

figure(2)
% imhist��������ʾͼ��ĻҶ�ֱ��ͼ
subplot(121),imhist(R,64),title('ԭʼֱ��ͼ');
subplot(122),imhist(S,64),title('������ֱ��ͼ');

end

