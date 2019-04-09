clc;
img=load('l256.dat');
img=uint8(img);
figure('Name','Actual'),imshow(img);
waitforbuttonpress;


new_img = gauss_avg(img,1000,2);
figure('Name','average'),imshow(new_img);
waitforbuttonpress;
