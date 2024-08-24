import { Module } from '@nestjs/common';
import { WeatherModule } from './weather.module';
import { WeatherService } from './weather.service';
import { WeatherController } from './weather.controller';

@Module({
  imports: [WeatherModule],
  providers: [WeatherService],
  controllers: [WeatherController],
})
export class WeatherHttpModule {}
