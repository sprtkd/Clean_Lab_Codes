clc;
img=load('l256.dat');
img=uint8(img);
figure('Name','Actual'),imshow(img);
waitforbuttonpress;

noisy_img = img_manipulate(img, 20, 30);
figure('Name','Noisy'),imshow(noisy_img);
waitforbuttonpress;

new_img = spatial_mean_filter(noisy_img,5);
figure('Name','MeanFiltered'),imshow(new_img);
waitforbuttonpress;

unsharp = abs(noisy_img - new_img);
figure('Name','Unsharp'),imshow(unsharp);
waitforbuttonpress;