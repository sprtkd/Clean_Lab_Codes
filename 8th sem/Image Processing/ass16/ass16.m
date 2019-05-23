clc;
img=load('l256.dat');
img=uint8(img);
figure('Name','Actual'),imshow(img);
waitforbuttonpress;

new_img = highboost(img, 1);
figure('Name','highboost'),imshow(new_img);
waitforbuttonpress;

