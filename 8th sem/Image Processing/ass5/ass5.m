clc;
img=load('l256.dat');
img=uint8(img);
figure('Name','Actual'),imshow(img);
%waitforbuttonpress;

new_img = img_manipulate(img, 50, 20);
figure('Name','manipulated'),imshow(new_img);