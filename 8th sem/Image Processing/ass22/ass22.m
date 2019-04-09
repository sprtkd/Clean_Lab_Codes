clc;
img=load('l256.dat');
img=uint8(img);
figure('Name','Actual'),imshow(img);
waitforbuttonpress;

new_img = rotate_theta(img,25);
figure('Name','shifted'),imshow(new_img);
