s = '
Port9 10000M wirespeed test (TX:46934673 RX:46934677 @ 9987.699M bps) PASS

Port10 10000M wirespeed test (TX:46934677 RX:46934673 @ 9987.698M bps) PASS

Port11 10000M wirespeed test (TX:46935008 RX:46935008 @ 9987.769M bps) PASS

Port12 10000M wirespeed test (TX:46935008 RX:46935008 @ 9987.769M bps) PASS

Wirespeed Test PASS 





Temp Remote 1: 90 C
Temp Local   : 45 C
Temp Remote 2: 36 C
Temp CPU     : 67 C
'

res = 'Wirespeed Test PASS' in s
print(res)
