# Create a New Sudo User
1. sudo adduser username
2. ...
3. sudo usermod -aG sudo username

# Test sudo access on new user account
1. su -username
2. sudo ls -la /root
