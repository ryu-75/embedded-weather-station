import { BadRequestException, Injectable } from '@nestjs/common';
import { Weather } from './weather.entity';
import { Repository } from 'typeorm';
import { InjectRepository } from '@nestjs/typeorm';

@Injectable()
export class WeatherService {
  constructor(
    @InjectRepository(Weather)
    private myWeather: Repository<Weather>,
  ) {}

  async create(weather: Partial<Weather>) {
    if (!weather) throw new BadRequestException('Data must be provided');

    const entity = this.myWeather.create(weather);

    console.log('Saving entity: ', entity);
    return await this.myWeather.save(entity);
  }

  findAll(): Promise<Weather[]> {
    if (!this.myWeather) throw new BadRequestException('My weather not found');
    return this.myWeather.find();
  }
}
