function [] = my_ideal()
% ʹ��DFT��IDFT���Լ�����ߡ���ͨ�˲���������Ƶ���˲�

% ��1������ȡͼ�񣬽���С��չΪ2M*2N�������0
f = imread('test2.tif');
f = im2double(f);
[M,N] = size(f);
fp=[f zeros(M,N); zeros(M,2*N)];

% ��2��������DFT����������Ƶ�����Ƶ�Ƶ������
%F = fftshift(fft2(fp));  % fft2��������ά���ٸ���Ҷ�任
F = fftshift(my_DFT(fp));  % fftshift���������ڽ���Ƶ�����Ƶ�Ƶ������

% ��3�����˲�
% ����˲���
u = -N:N-1;
v = -M:M-1;
[U,V] = meshgrid(u,v);       % meshgrid���������ɾ���U��V������Ԫ��ֵ���������ڵ��У��У� 
D = hypot(U,V);              % hypot��������ÿ��Ԫ�ص�ƽ����������Ƶ�����ľ���
D0 = 30;                     % ��ֹƵ������Ϊ30
ILPF = mat2gray( D <= D0 );  % �����ͨ�˲���
IHPF = mat2gray( D > D0 );   % �����ͨ�˲���
% Ƶ���˲�
G1 = F.*ILPF;
G2 = F.*IHPF;
 
% ��4������ԭƵ�׵�λ�ã�����IDFT��ȡʵ�����ü�
% gp1 = ifft2(fftshift(G1));
gp1 = my_IDFT(fftshift(G1));
% gp2 = ifft2(fftshift(G2));
gp2 = my_IDFT(fftshift(G2));
g1 = real(gp1);    % ȡʵ��
g2 = real(gp2);
g1 = g1(1:M,1:N);  % �ü������0������
g2 = g2(1:M,1:N);

% ��5����������
fprintf('������:\n');
figure;
subplot(2,2,1);imshow(f);title('ԭͼ');
subplot(2,2,2);imshow(mat2gray(log(1+abs(F))));title('����ҶƵ��');
subplot(2,2,3);imshow(g1);title('�����ͨ�˲����ͼ��');
subplot(2,2,4);imshow(g2);title('�����ͨ�˲����ͼ��');
end