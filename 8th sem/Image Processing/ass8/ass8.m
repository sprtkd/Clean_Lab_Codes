clc;
img=load('l256.dat');
img=uint8(img);
figure('Name','Actual'),imshow(img);
waitforbuttonpress;

noisy_img = img_manipulate(img, 20, 20);
figure('Name','Noisy'),imshow(noisy_img);
waitforbuttonpress;

new_img = spatial_mean_filter(noisy_img,3);
figure('Name','MeanFiltered'),imshow(new_img);
waitforbuttonpress;

new_img = spatial_median_filter(noisy_img,3);
figure('Name','MedianFiltered'),imshow(new_img);
waitforbuttonpress;