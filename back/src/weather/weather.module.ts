import { Module } from '@nestjs/common';
import { TypeOrmModule } from '@nestjs/typeorm';
import { WeatherSchema } from './weather.schema';
import { WeatherService } from './weather.service';
import { WeatherController } from './weather.controller';

@Module({
  imports: [TypeOrmModule.forFeature([WeatherSchema])],
  providers: [WeatherService],
  controllers: [WeatherController],
})
export class WeatherModule {}
