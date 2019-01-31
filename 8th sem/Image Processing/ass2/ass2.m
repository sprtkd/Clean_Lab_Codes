clc;
img=load('l256.dat');
img=uint8(img);
figure('Name','Actual'),imshow(img);
waitforbuttonpress;

new_img = downsampler(img);
figure('Name','Down 1'),imshow(new_img);
waitforbuttonpress;

new_img = downsampler(new_img);
figure('Name','Down 2'),imshow(new_img);
waitforbuttonpress;

new_img = upsampler(img);
figure('Name','Up 1 copying'),imshow(new_img);
waitforbuttonpress;
new_img = upsampler(new_img);
figure('Name','Up 2 copying'),imshow(new_img);
waitforbuttonpress;

new_img = upsampler_avg(img);
figure('Name','Up 1 avg'),imshow(new_img);
waitforbuttonpress;
new_img = upsampler(new_img);
figure('Name','Up 2 avg'),imshow(new_img);
waitforbuttonpress;

new_img = img_neg(img);
figure('Name','Neg'),imshow(new_img);