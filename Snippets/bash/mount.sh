#! /bin/bash

usb_exists() {
  local usb_name=$1
  echo "usb_name: ${usb_name}"

  local df_output=$(df -h | grep $usb_name)
  echo "df_output: ${df_output}"

  if [[ $df_output == *"$usb_name"* ]]; then
    device_name="${df_output%% *}"
    echo "${df_output}"
    echo "exists! = ${device_name}"
    return ${device_name}  # Substring found, return 1
  else
    echo "doesn't exist!"
    return 0  # Substring not found, return 0
  fi
}

get_device_name() {
  local KEY=$1
  local df_output=$(df -h | grep ${KEY})

  if [[ $df_output == *"$usb_name"* ]]; then
    device_name="${df_output%% *}"
    echo "${device_name}"
  else
    echo "0"
  fi
}

get_mount_point() {
  device_name="$1"
  # Use the 'findmnt' command to get the mount point
  mount_point=$(findmnt -n -o TARGET --source "$device_name")
  echo "$mount_point"
}

read -p "Enter the usb key: " usb_key

# If mounted, unmount first!
device_name=$(get_device_name ${usb_key})
echo "Found device is '${device_name}'"

if [ "device_name" != "0" ]; then
  mount_point=$(get_mount_point "${device_name}")
  echo "Found mount point is '${mount_point}'"
  sudo umount "${mount_point}"
fi

echo "Mount '${device_name}' on '/home/leecw/USB_T7_2TB'"
sudo mount -t exfat ${device_name} /home/leecw/USB_T7_2TB
