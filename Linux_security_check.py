import subprocess
import re

def check_security_updates():
  try:
    apt_list = subprocess.run(["sudo", "apt", "list"], capture_output=True).stdout.decode()
    if re.search(r"upgradable", apt_list):
      return "Security updates available! Run 'sudo apt upgrade' to install."
    else:
      return "No security updates found."
  except subprocess.CalledProcessError:
    return "Error checking for updates."

def check_failed_root_logins(log_file="/var/log/auth.log"):
  try:
    with open(log_file, 'r') as log:
      failed_logins = len(re.findall(r"sshd: Failed password for root", log.read()))
      if failed_logins > 0:
        return f"WARNING: {failed_logins} failed root login attempts found in {log_file}"
      else:
        return "No failed root login attempts found."
  except FileNotFoundError:
    return f"Error: Log file {log_file} not found."

def check_disabled_users():
  try:
    disabled_users = subprocess.run(["awk", "-F:", '$3 == 1000 {print $1}', "/etc/passwd"], capture_output=True).stdout.decode().strip()
    if disabled_users:
      return f"WARNING: Disabled user accounts found:\n{disabled_users}"
    else:
      return "No disabled user accounts found."
  except subprocess.CalledProcessError:
    return "Error checking for disabled users."

def check_open_ports():
  try:
    netstat_output = subprocess.run(["netstat", "-tlpn"], capture_output=True).stdout.decode()
    open_ports = [line.split()[3] for line in netstat_output.splitlines() if re.search(r"LISTEN", line)]
    if open_ports:
      return f"Open ports found:\n{', '.join(open_ports)}"
    else:
      return "No open ports found (excluding standard services)."
  except subprocess.CalledProcessError:
      return "Error checking for open ports."

if __name__ == "__main__":
  print("Checking for security updates...")
  print(check_security_updates())
  print("Checking for failed root login attempts...")
  print(check_failed_root_logins())
  print("Checking for disabled user accounts...")
  print(check_disabled_users())
  print("Checking for open ports...")
  print(check_open_ports())
  print("Security check completed.")
