clc;
img=load('l256.dat');
img=uint8(img);
figure('Name','Actual'),imshow(img);
waitforbuttonpress;

new_img = translate_xy(img,5,10);
figure('Name','shifted'),imshow(new_img);
