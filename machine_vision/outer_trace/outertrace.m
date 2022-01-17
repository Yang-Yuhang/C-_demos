R=imread('D:\课件\机器视觉基础\课件\外边界跟踪/NKU.jpg');
figure('Name','RGB彩色图');
imshow(R);
Imggray=rgb2gray(R);%化为灰度图
figure('Name','灰度图像');
imshow(Imggray);

[m,n]=size(Imggray);%获取图像大小
t=graythresh(Imggray);%确定阈值
ImgBinary=imbinarize(Imggray,t);%二值化
figure('Name','二值图');
imshow(ImgBinary);

ImgBoundary=zeros(m,n,1);%创建外边界图像
ed=[1 0;1 -1;0 -1;-1 -1;-1 0;-1 1;0 1;1 1];% 8-邻接区域，右开始
for i=2:m-1%获取外边界图像无法顶到图像边界
    for j=2:n-1
        if ImgBinary(i,j)==1%当前像素是物体
            for k=1:8%遍历8-邻接区域
                x=i+ed(k,1);
                y=j+ed(k,2);
                if ImgBinary(x,y)==0    %当前像素是背景，标记为外边界
                    ImgBoundary(x,y)=1;
                end
            end 
        end
    end
end

figure('Name','图像外边界');
imshow(ImgBoundary,[]);