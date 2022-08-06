function y = myQuantizer(x,B,Xm)
LevelQuantization = 2^(B-1);
Delta = Xm/LevelQuantization;
Normal = x/Delta;

for i=1:length(x)
    for k=(-LevelQuantization):(LevelQuantization-1)
        if Normal(i)>=k && Normal(i)<=(k+1)
           y(i) = (k+0.5)*Delta;
        elseif Normal(i)<-(LevelQuantization)
           y(i) = (-(LevelQuantization+0.5))*Delta;
        elseif Normal(i)> (LevelQuantization)
           y(i )= (LevelQuantization+0.5)*Delta;
        end
    end
end
end