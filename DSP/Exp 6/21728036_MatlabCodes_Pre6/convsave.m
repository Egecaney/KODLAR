% Egemen Can Ayduðan - 21728036
% Preliminary Work 6

function y = convsave(x,h,L)
 
LengthH1 = length(h);
LengthX = length(x);
N = L+LengthH1-1; 

H = [h zeros(1,L-1)];
LengthH2 = length(H);

X1 = reshape(x,[L LengthX/L]); 
X2 = X1((L-LengthH1+2:L),:); 
X2 = [zeros(LengthH1-1,1) X2(:,(1:((LengthX/L)-1)))]; 
X1 = [X2;X1];

LengthX1 = length(X1);
H = repmat(H',1,LengthX/L); 
Xz = zeros(N-LengthX1,LengthX/L);
Hz = zeros(N-LengthH2,LengthX/L);
 
x = [X1;Xz];
H = [H;Hz];
X = fft(x,N);
H = fft(H,N);
Yr = X.*H;
yr = ifft(Yr,L+LengthH1-1);
yr = yr(LengthH1:L+LengthH1-1,:); 
y = yr(:);
 
end