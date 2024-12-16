import json
from http.server import BaseHTTPRequestHandler, HTTPServer

class EchoRequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        # Send response headers
        self.send_response(200)
        self.send_header('Content-type', 'application/json')
        self.end_headers()

        # Echo the requested path as a JSON response
        response = {'echo': self.path}
        self.wfile.write(json.dumps(response).encode('utf-8'))

    def do_POST(self):
        # Send response headers
        self.send_response(200)
        self.send_header('Content-type', 'application/json')
        self.end_headers()

        # Read and echo the data received in the POST request
        content_length = int(self.headers['Content-Length'])
        post_data = self.rfile.read(content_length)

        response = {'echo': post_data.decode('utf-8')}
        self.wfile.write(json.dumps(response).encode('utf-8'))

def run(server_class=HTTPServer, handler_class=EchoRequestHandler, port=8057):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting echo server on port {port}...')
    httpd.serve_forever()

if __name__ == "__main__":
    run()
