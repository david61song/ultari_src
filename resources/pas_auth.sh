METHOD="$1"
MAC="$2"

./auth_curl auth_client "$2" "$3" "$4"

case "$METHOD" in
	auth_client)
		if [ "$?" -eq 0 ]; then
			# Allow client to access the Internet for one hour (3600 seconds)
			# # Further values are upload and download limits in bytes. 0 for no limit.
			echo 3600 0 0
			exit 0
		elif [ "$?" -eq 2 ]; then
			echo 1200 0 0
			exit 0
		else
      			# Deny client to access the Internet.
      			exit 1
	 fi
  ;;
  client_auth|client_deauth|idle_deauth|timeout_deauth|ultarictl_auth|ultarictl_deauth|shutdown_deauth)
  INGOING_BYTES="$3"
  OUTGOING_BYTES="$4"
  SESSION_START="$5"
  SESSION_END="$6"
    # client_auth: Client authenticated via this script.
    # client_deauth: Client deauthenticated by the client via splash page.
    # idle_deauth: Client was deauthenticated because of inactivity.
    # timeout_deauth: Client was deauthenticated because the session timed out.
    # ultarictl_auth: Client was authenticated by the ultarictl tool.
    # ultarictl_deauth: Client was deauthenticated by the ultarictl tool.
    # shutdown_deauth: Client was deauthenticated by Ultari terminating.
    ;;
    esac
