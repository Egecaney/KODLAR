function y = myAdaptiveQuantizer(x,B,L)

for i = 1:round(length(x)/L)
    First = ((i-1)*L)+1;
    y(First:i*L) = myQuantizer(x(First:i*L),B,max(x(First:i*L)));
end

end