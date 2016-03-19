import socket
import subprocess
import time


class BrowserController:
    def __init__(self):
        pass

    process = None

    def navigate_to(self, url):
        if self.process is not None:
            self.process.poll()
            if self.process.returncode is None:
                print("Browser seems to be running fine. Sending command...")

                try:
                    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                    s.connect(('127.0.0.1', 32000))
                    s.send('window.location.href="%s"' % url)
                    s.close()
                except Exception as e:
                    print("Couldn't send command to remote control")

                return
            else:
                print("Browser died. Restarting...")
        else:
            print("Launching browser...")

        devnull = open('/dev/null', 'w')
        self.process = subprocess.Popen(['iceweasel', '--display=:0', url], stdout=devnull, stderr=devnull)
