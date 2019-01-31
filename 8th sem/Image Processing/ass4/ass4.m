clc;
img=load('l256.dat');
img=uint8(img);
figure('Name','Actual'),imshow(img);
%waitforbuttonpress;

new_img = gray_slicer(img, 50, 170);
figure('Name','sliced'),imshow(new_img);