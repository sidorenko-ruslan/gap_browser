

require 'socket'
require 'json'
sock = TCPSocket.new('127.0.0.1', 3000)
sock.write({ "command" => 'goto', 'command_data' => 'https://www.slo.ru' }.to_json)
puts sock.read(15) # Since the response message has 5 bytes.
sock.close

