
entry = ope_low
ope_low = ope_high , ( ('+' | '-') , ope_high)*
ope_high = num , (('\*' | '/' | '\%') , num)*
num = ('1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9' | '0')+
