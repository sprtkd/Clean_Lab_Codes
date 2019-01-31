function y = thresholder(img, threshval)
[row,col,channels]=size(img);
if channels~=1
    img = rgb2gray(img);
end
new_img=zeros(row,col);
for i=1:row
    for j=1:col
        if img(i,j)>=threshval
            new_img(i,j)=1;
        else
            new_img(i,j)=0;
        end
    end
end
y=new_img;
end