# Cytis
## A centralized tire inflation system for bicycles

## Summary 
  How many times have you been on a ride and forgot to check the tire pressure before hitting the road (or the trails) or you were changing the terrain and you haven't got that perfect pressure. Well this product helps to prevent you from getting in that situation by allowing you to control how much air you got in your tires directly from your phone, or any device with bluetooth.
  
## What is Cytis made of 
  For a start I am using an Arduino Nano hooked up to a CO2 canister connected with a hose to the air valve. The device will be mounted on the hub of the wheel in order to be less noticeable.
  For the phone interface I've made a web app using Ruby on Rails, there, you can connect to the device using Web Bluetooth and create presets, after signing up.
  
## Main functions
 * Read the current air pressure
 * Inflate the tire
 * Deflate the tire 
 
## Technologies used
 * Arduino ecosystem
 * Ruby on Rails
 * Web Bluetooth
 * PWA

## System Requirements
 * device capable of accesing the Internet using a Web Bluetooth compatible browser(currently Chrome or Opera)

## Do you want to run the web interface locally?
* Have RoR v6.1.4 installed and Ruby v3.0.3
* Run `git clone git@github.com:sipandrei/Cytis_frontend.git`
* Run `bundle install`
* Run `rails db:migrate`
* Start the server and you should have a working Cytis web interface  
