import { Controller, Post, Get, Body } from '@nestjs/common';
import { WeatherService } from 'src/weather/weather.service';
import { Weather } from 'src/weather/weather.entity';

@Controller('weather')
export class WeatherController {
  constructor(private weatherService: WeatherService) {}
  @Post()
  async create(@Body() weather: Weather) {
    return this.weatherService.create(weather);
  }

  @Get()
  async findAll() {
    return this.weatherService.findAll();
  }
}
