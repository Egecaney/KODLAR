% Egemen Can Ayduðan - 21728036
% Preliminary Work 6

function y = convadd(x,h,L)

LengthX = length(x);
LengthH = length(h);
N = L+LengthH-1;

h = [h zeros(1,L-1)];
LengthY2 = length(h);
h = repmat(h',1,(LengthX/L));

x1 = reshape(x,[L LengthX/L]);
xz1 = zeros((LengthH-1),LengthX/L);
x2 = [x1;xz1];
LengthX2 = length(x2);
xz2 = zeros(N-LengthX2,LengthX/L);
hz = zeros(N-LengthY2,LengthX/L);

x = [x2;xz2];
h = [h;hz];
X = fft(x,N);
H = fft(h,N);

Yr = X.*H;
yr = ifft(Yr,N);
yradd = yr((N-LengthH+2:N),:);
yradd = [zeros(LengthH-1,1) yradd(:,(1:((LengthX/L)-1)))];
yradd2=  [yradd;zeros(L,LengthX/L)];
y = yradd2 + yr;
y = y(1:L,:);
y = y(:);

end


