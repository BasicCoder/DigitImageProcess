# Shadowsocks(python Version)
---
# * **Client Use** *
> 1. ss client download and install
> 2. ss server address: ****
> 3. Remote Port: 17 + 学号后三位
> 4. Local Port:2160
> 5. Password:学号
> 6. Encrypt Method:RC4-MD5
> 7. (Optional) Ipv6 Route turn on
> 8. (Optional) DNS Forwarding turn on

---

## Environment
> 1. Ubuntu 16.04 LTS
## Configuration
### Install 
> 1. `apt install python-pip python-m2crypto python-wheel python-setuptools`
> 2. `pip install shadowsocks`

### Configure
> `vi /etc/shadowsocks.json`

> ` {`   
> `     "server":"server_ip",`  
> `     "port_password":{`  
> `          "1000":"password1",`  
> `          "1001":"password2",`  
> `          "1001":"password2",`  
> `     },`  
> `     "timeout":600,`  
> `     "method":"rc4-md5",`    
> `     "fast_open": false`  
> ` }`

## Run and Stop
> `ssserver -c /etc/shadowsocks.json -d start`  
> `ssserver -c /etc/shadwosocks.json -d stop`