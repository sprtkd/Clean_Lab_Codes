clc;
img=load('l256.dat');
img=uint8(img);
figure('Name','Actual'),imshow(img);
waitforbuttonpress;

new_img = delxy(img);
figure('Name','delxy'),imshow(new_img);
waitforbuttonpress;

