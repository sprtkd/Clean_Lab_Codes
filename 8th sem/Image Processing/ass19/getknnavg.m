function [ knn_avg ] = getknnavg( input_arr, point_val, k )
    [~,N] = size(input_arr);
    dists = zeros(N,1);
    for idx = 1 : N
        dists(idx) = sum(abs(input_arr(idx) - point_val));
    end
    [~,ind] = sort(dists);
    ind_closest = ind(1:k+1);
    kmeanslist = input_arr(ind_closest);
    kmeanslist(1) = [];
    knn_avg = round(mean(kmeanslist));
end

