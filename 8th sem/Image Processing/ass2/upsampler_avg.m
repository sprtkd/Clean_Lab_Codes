function [ up_img ] = upsampler_avg( img )
[row,col,channels]=size(img);
new_row = round(row*2);
new_col = round(col*2);

up_img = zeros(new_row,new_col,1);

%Copying
for i=1:row
    for j=1:col
        new_i=i*2-1;
        new_j=j*2-1;
        up_img(new_i,new_j) = img(i,j);
    end
end

%filling avg in alternate rows and columns
for i=1:new_row
    for j=1:new_col
        if mod(i,2)==0 && mod(j,2)==1 && i+1<=new_row
            p1 = up_img(i-1,j);
            p2 = up_img(i+1,j);
            up_img(i,j) = (p1+p2)/2;
        end            
        if mod(i,2)==1 && mod(j,2)==0 && j+1<=new_col
            p1 = up_img(i,j-1);
            p2 = up_img(i,j+1);
            up_img(i,j) = (p1+p2)/2;

        end
    end
end

%filling avg in middle voids
for i=1:new_row
    for j=1:new_col
        if mod(i,2)==0 && mod(j,2)==0 && i+1<=new_row && j+1<=new_col
            p1 = up_img(i-1,j);
            p2 = up_img(i+1,j);
            p3 = up_img(i,j-1);
            p4 = up_img(i,j+1);
            up_img(i,j) = (p1+p2+p3+p4)/4;
        end            
    end
end

up_img = uint8(up_img);
end

