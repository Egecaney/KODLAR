function y = mySNR(x,xquan)

Error = x-xquan;

y(1) = 10*log10(var(x)./var(Error));
y(2) = 10*log10(var(xquan)./var(Error));

end