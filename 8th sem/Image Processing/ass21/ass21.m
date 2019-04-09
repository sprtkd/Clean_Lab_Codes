clc;
img=load('l256.dat');
img=uint8(img);
figure('Name','Actual'),imshow(img);
waitforbuttonpress;

new_img = scaling_xy(img,1.4,1.6);
figure('Name','shifted'),imshow(new_img);
