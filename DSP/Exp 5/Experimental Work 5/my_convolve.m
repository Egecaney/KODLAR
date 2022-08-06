function [y] = myConv(x,h)

diff = length(x)-length(h);
h = [h zeros(1,diff)];
z_x = zeros(1,length(x));
z_x(1) = x(1);
X = toeplitz(x,z_x);
H = h';
Y = X*H;
y = [Y' x(end)*h(end-diff)];

end
