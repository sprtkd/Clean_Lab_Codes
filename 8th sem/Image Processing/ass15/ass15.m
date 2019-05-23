clc;
img=load('f256.dat');
img=uint8(img);
figure('Name','Actual'),imshow(img);
waitforbuttonpress;

new_img = laplacian(img);
figure('Name','laplacian'),imshow(new_img);
waitforbuttonpress;

