% Egemen Can Ayduðan - 21728036
% Preliminary Work 6

function y = dftsave(x,h,L)
 
LengthX = length(x);
LengthH = length(h);

h = [h zeros(1,L-1)];
N = L + LengthH-1;
 
X1 = reshape(x,[L LengthX/L]);
X2 = X1((L-LengthH+2:L),:);
X2 = [zeros(LengthH-1,1) X2(:,(1:((LengthX/L)-1)))];
X1 = [X2;X1]; 
h = repmat(h',1,LengthX/L);
 
X = fft(X1,N);
H = fft(h,N);
Yr = X.*H;
yr = ifft(Yr,L+LengthH-1);
yr = yr(LengthH:L+LengthH-1,:);
y = yr(:);
 
end