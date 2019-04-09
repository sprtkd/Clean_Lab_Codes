function [ new_img ] = spatial_mean_filter_thresh( img, filter_n, thresh )
[row,col,channels]=size(img);

adder = round((filter_n - 1)/2)

padded_img = double(zeros(row+(adder*2),col+(adder*2),1));
filtered_img = double(zeros(row+(adder*2),col+(adder*2),1));
new_img = double(zeros(row,col,1));
for i=1:row
    for j=1:col
        padded_img(i+adder,j+adder) = img(i,j);
    end
end

kernel = double(zeros(filter_n,filter_n,1));

value=1/(filter_n*filter_n);

for i=1:filter_n
    for j=1:filter_n
        kernel(i,j)= value;
    end
end

for i=1+adder:row
    for j=1+adder:col
        if(mod(filter_n,2)==0)
            extracted = padded_img([(i-adder):(i+adder-1)],[(j-adder):(j+adder-1)]);
        else
            extracted = padded_img([(i-adder):(i+adder)],[(j-adder):(j+adder)]);
        end
        conv =(extracted.*kernel);
        filtered_img(i,j) = sum(conv(:));
    end
end

i_n=1;
for i=1+adder:row
    j_n=1;
    for j=1+adder:col
        new_img(i_n,j_n) = filtered_img(i,j);
        j_n = j_n+1;
    end
    i_n = i_n+1;
end

new_img = uint8(new_img);
delta = abs(new_img - img);

for i=1:row
    for j=1:col
        if(delta(i,j) > thresh)
            img(i,j) = new_img(i,j);
        end
    end
end

new_img = uint8(img);
end

