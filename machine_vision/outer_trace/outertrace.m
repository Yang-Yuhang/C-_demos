R=imread('D:\�μ�\�����Ӿ�����\�μ�\��߽����/NKU.jpg');
figure('Name','RGB��ɫͼ');
imshow(R);
Imggray=rgb2gray(R);%��Ϊ�Ҷ�ͼ
figure('Name','�Ҷ�ͼ��');
imshow(Imggray);

[m,n]=size(Imggray);%��ȡͼ���С
t=graythresh(Imggray);%ȷ����ֵ
ImgBinary=imbinarize(Imggray,t);%��ֵ��
figure('Name','��ֵͼ');
imshow(ImgBinary);

ImgBoundary=zeros(m,n,1);%������߽�ͼ��
ed=[1 0;1 -1;0 -1;-1 -1;-1 0;-1 1;0 1;1 1];% 8-�ڽ������ҿ�ʼ
for i=2:m-1%��ȡ��߽�ͼ���޷�����ͼ��߽�
    for j=2:n-1
        if ImgBinary(i,j)==1%��ǰ����������
            for k=1:8%����8-�ڽ�����
                x=i+ed(k,1);
                y=j+ed(k,2);
                if ImgBinary(x,y)==0    %��ǰ�����Ǳ��������Ϊ��߽�
                    ImgBoundary(x,y)=1;
                end
            end 
        end
    end
end

figure('Name','ͼ����߽�');
imshow(ImgBoundary,[]);