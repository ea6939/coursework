function result = remove_noise(B,mu,s)


%first step, magnitude averaging of the signal spectrum over three time windows 
%this step does not seem very useful as it is not a varying environment
for d = s:length(B(:,1))
    if((d>1) && (d<length(B(:,1))))
     Y(d,:)=  1/3*(abs(B(d-1,:))+ abs(B(d,:))+ abs(B(d+1,:)));
    end
    if(d==1)
     Y(d,:)=  (1/2)* (abs(B(d,:))+ abs(B(d+1,:)));
    end
    if (d==length(B(:,1)))
     Y(d,:)=  (1/2)*(abs(B(d-1,:))+ abs(B(d,:)));
    end     
end

%removal of mean of noise and half-wave rectification
 
%then we substract from Y the mean error computed earlier and and give it
%the phase of the original X
for h = 1:length(B(:,1))
    for j=1:length(B(1,:))
        %substarct the mean of the noise to the signal only when the  original signal
        %is bigger than the mean of noise
        if(Y(h,j)-mu(j)>0)
        Y(h,j)=(Y(h,j)-mu(j))*exp(1i*angle(B(h,j)));
        else   
        %here perform half-wave rectification if signal smaller than mean
        %of error
        Y(h,j)=0;
        end
    end
end    

%compute maximum noise residual nr
%fill the noise residual array
nr=1:length(B(1,:));
for j=1:length(B(1,:))
    for h = 1:s
        if(abs(B(h,j))>nr(j))
            nr(j)=abs(Y(h,j)-B(h,j));
        end
    end
end


%residual noise removal

% remove frequencies that are below the maximum noise residual if the
% magnitude is bigger than the one for the previous or the next frame, and
% replace accordingly by the smallest value
for h = 1:length(B(1,:))
    for j=1:length(B(:,1))
       %if the magnitude of the noise residual at that frequency is smaller than the maximum magnitude of noise measured at on speech activity 
       if(abs(Y(j,h)-B(j,h))<nr(h)) 
           
       if((j>1) && (j<length(B(:,1))))
            if(abs(Y(j,h)-B(j,h))>abs(Y(j+1,h)-B(j+1,h)) && abs(Y(j-1,h)-B(j-1,h))>abs(Y(j+1,h)-B(j+1,h)))
            Y(j,h)=abs(Y(j+1,h))*exp(1i*angle(Y(j,h)));
            elseif(abs(Y(j,h)-B(j,h))>abs(Y(j-1,h)-B(j-1,h)) && abs(Y(j+1,h)-B(j+1,h))>abs(Y(j-1,h)-B(j-1,h)))
            Y(j,h)=abs(Y(j-1,h))*exp(1i*angle(Y(j,h)));
            end
       end
      %%%%%%%%%%% 
       if(j==1)
        if(abs(Y(j,h)-B(j,h))>abs(Y(j+1,h)-B(j+1,h)))
            Y(j,h)=abs(Y(j+1,h))*exp(1i*angle(Y(j,h)));
        end
       end
      %%%%%%%%%%% 
       if (j==length(B(:,1)))
         if(abs(Y(j,h)-B(j,h))>abs(Y(j-1,h)-B(j-1,h)))
            Y(j,h)=abs(Y(j-1,h))*exp(1i*angle(Y(j,h)));
         end
       end 
       
       end
    end
end

result = Y;