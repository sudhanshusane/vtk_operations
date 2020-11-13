#include <vtkm/io/VTKDataSetReader.h>
#include <vtkm/io/VTKDataSetWriter.h>
#include <vtkm/cont/DataSet.h>
#include <vtkm/cont/VariantArrayHandle.h>
#include <vtkm/cont/ArrayHandleVirtual.h>
#include <vtkm/cont/Initialize.h>
#include <vtkm/Bounds.h>
#include <vtkSmartPointer.h>
#include <vtkPointData.h>
#include <vtkFloatArray.h>
#include <vtkDoubleArray.h>
#include <vtkDataArray.h>
#include <vtkDataSetWriter.h>
#include <vtkRectilinearGrid.h>

#include <iostream>
#include <sstream>


int main(int argc, char *argv[])
{
	vtkm::io::VTKDataSetReader reader(argv[1]);
	vtkm::cont::DataSet ds = reader.ReadDataSet();
	
	std::string output_path(argv[2]);

	int dims[3];
	dims[0] = atoi(argv[3]);
	dims[1] = atoi(argv[4]);
	dims[2] = atoi(argv[5]);
	
  vtkm::cont::VariantArrayHandle field_u = ds.GetPointField("u").GetData();
  vtkm::cont::VariantArrayHandle field_v = ds.GetPointField("v").GetData();

  vtkm::cont::ArrayHandleVirtual<vtkm::Float32> u_FieldArray =  field_u.AsVirtual<vtkm::Float32>();
  vtkm::cont::ArrayHandle<vtkm::Float32> u_fieldArray = u_FieldArray.Cast<vtkm::cont::ArrayHandle<vtkm::Float32>>();

  vtkm::cont::ArrayHandleVirtual<vtkm::Float32> v_FieldArray =  field_v.AsVirtual<vtkm::Float32>();
  vtkm::cont::ArrayHandle<vtkm::Float32> v_fieldArray = v_FieldArray.Cast<vtkm::cont::ArrayHandle<vtkm::Float32>>();

	vtkm::Bounds bounds = ds.GetCoordinateSystem().GetBounds();
	float bbox[6];
	bbox[0] = bounds.X.Min;
	bbox[1] = bounds.X.Max;
	bbox[2] = bounds.Y.Min;
	bbox[3] = bounds.Y.Max;
	bbox[4] = bounds.Z.Min;
	bbox[5] = bounds.Z.Max;

	float x_spacing = (bbox[1]-bbox[0])/(dims[0]-1);
	float y_spacing = (bbox[3]-bbox[2])/(dims[1]-1);

  auto u_val = u_fieldArray.ReadPortal();
  auto v_val = v_fieldArray.ReadPortal();

	
	float *u = (float*)malloc(sizeof(float)*dims[0]*dims[1]);
	float *v = (float*)malloc(sizeof(float)*dims[0]*dims[1]);


  vtkSmartPointer<vtkFloatArray> xCoords =
    vtkSmartPointer<vtkFloatArray>::New();
  vtkSmartPointer<vtkFloatArray> yCoords =
    vtkSmartPointer<vtkFloatArray>::New();

	for(int i = 0; i < dims[0]; i++)
	{
		xCoords->InsertNextValue(bbox[0]+(i*x_spacing));
	}
	
	for(int i = 0; i < dims[1]; i++)
	{
		yCoords->InsertNextValue(bbox[2]+(i*y_spacing));
	}


	for(int i = 0; i < dims[2]; i++)
	{
		// Populate the velArray with values from this slice
		vtkSmartPointer<vtkFloatArray> uArray = vtkSmartPointer<vtkFloatArray>::New();
		uArray->SetName("u");
		uArray->SetNumberOfComponents(1);
		vtkSmartPointer<vtkFloatArray> vArray = vtkSmartPointer<vtkFloatArray>::New();
		vArray->SetName("v");
		vArray->SetNumberOfComponents(1);
		for(int j = 0; j < dims[1]; j++)
		{
			for(int k = 0; k < dims[0]; k++)
			{
				int index = i*dims[0]*dims[1] + j*dims[0] + k;
				uArray->InsertNextValue(u_val.Get(index));
				vArray->InsertNextValue(v_val.Get(index));
			}
		}
			// Write out a VTK file for this value of time.		

		vtkSmartPointer<vtkDataSetWriter> writer =
    	vtkSmartPointer<vtkDataSetWriter>::New();

  	vtkSmartPointer<vtkRectilinearGrid> outputGrid =
      vtkSmartPointer<vtkRectilinearGrid>::New();

  	outputGrid->SetDimensions(dims[0], dims[1], 1);
  	outputGrid->SetXCoordinates(xCoords);
  	outputGrid->SetYCoordinates(yCoords);

  	outputGrid->GetPointData()->AddArray(uArray);
  	outputGrid->GetPointData()->AddArray(vArray);

  	std::stringstream s;
  	s << output_path <<  "KVS_" << std::setfill('0') << std::setw(5) << i << ".vtk";

  	writer->SetFileName(s.str().c_str());
  	writer->SetInputData(outputGrid);
  	writer->SetFileTypeToASCII();
	  writer->Write();

	}


}

