function [w] = mybart(M)

Middle = round((M+1)/2);
n = 0:M;
w(1:Middle) = 2*n(1:Middle)/M;
w(Middle+1:M+1) = 2-(2*n(Middle+1:end)/M);

end
